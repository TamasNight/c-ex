"""
palette_optimizer.py
Ottimizza K palette da 16 colori per un tileset suddiviso in blocchi 8x8.
Genera K file .pal (JASC-PAL) e un JSON di mapping dei blocchi.
"""

from PIL import Image
import argparse, os, json, math
from collections import Counter, defaultdict
import itertools
import sys

# ---------- utility colore ----------
def hex_to_rgb(h):
    h = h.lstrip('#')
    if len(h) == 6:
        return tuple(int(h[i:i+2], 16) for i in (0,2,4))
    raise ValueError("Formato esadecimale non valido: " + h)

def rgb_dist(a, b):
    # distanza euclidea semplice in RGB
    return math.sqrt((a[0]-b[0])**2 + (a[1]-b[1])**2 + (a[2]-b[2])**2)

# ---------- estrazione blocchi 8x8 ----------
def extract_blocks(img, block_size=8, ignore_transparent_colors=None):
    img = img.convert("RGBA")
    w, h = img.size
    if w % block_size != 0 or h % block_size != 0:
        raise ValueError("L'immagine deve essere multipla del block_size")
    cols = w // block_size
    rows = h // block_size
    blocks = []
    for by in range(rows):
        for bx in range(cols):
            left = bx*block_size; top = by*block_size
            block = img.crop((left, top, left+block_size, top+block_size))
            pixels = list(block.getdata())
            cnt = Counter()
            for px in pixels:
                # se ha canale alpha e alpha==0 possiamo considerarlo trasparente:
                if len(px) == 4 and px[3] == 0:
                    continue
                rgb = px[0:3]
                if ignore_transparent_colors and rgb in ignore_transparent_colors:
                    # se uno dei colori passati come "trasparenza" lo consideriamo trasparente
                    continue
                cnt[rgb] += 1
            blocks.append({
                "bx": bx, "by": by, "colors": dict(cnt), "total_pixels": sum(cnt.values())
            })
    return blocks, cols, rows

# ---------- merging di una lista di colori con limite N ----------
def try_reduce_colors(color_counter, fixed_colors, max_colors=16, tol_start=12, tol_step=8, tol_max=120):
    """
    color_counter: Counter{(r,g,b): count} - colori da preservare/merge
    fixed_colors: list of colors already reserved (e.g. transparency color(s)) - will be kept
    Restituisce: (success:bool, final_colors_counter:Counter)
    Strategia:
      - tentiamo merge iterativi: rimuovere il colore meno frequente unendolo al colore più vicino (distanza <= tol)
      - aumentiamo tolleranza progressivamente fino a tol_max
      - se ancora troppi colori -> ritorna False
    """
    # inizializziamo con fixed colors forzati dentro
    c = Counter(color_counter)  # copia
    for fc in fixed_colors:
        if fc not in c:
            c[fc] = 0

    if len(c) <= max_colors:
        return True, c

    # tenteremo con tolleranze crescenti
    tol = tol_start
    while tol <= tol_max:
        c_work = Counter(c)
        changed = True
        # cerchiamo di ridurre finché possibile e fino a raggiungere max_colors
        while changed and len(c_work) > max_colors:
            changed = False
            # ordiniamo per frequenza crescente (rimuoviamo da meno frequente)
            items = sorted(c_work.items(), key=lambda t: t[1])
            for col, cnt in items:
                # non rimuovere fixed color
                if col in fixed_colors:
                    continue
                # trova il colore rimanente più vicino a distanza <= tol
                candidates = [(other, rgb_dist(col, other)) for other in c_work.keys() if other != col]
                if not candidates:
                    continue
                nearest, dist = min(candidates, key=lambda x: x[1])
                if dist <= tol:
                    # unisci col in nearest
                    c_work[nearest] += c_work[col]
                    del c_work[col]
                    changed = True
                    break
            # se nessuna modifica -> break while changed
        if len(c_work) <= max_colors:
            return True, c_work
        tol += tol_step

    # non siamo riusciti a rientrare nel budget con strategie tolleranti
    return False, c

# ---------- assegnazione blocchi a palette ----------
def assign_blocks_to_palettes(blocks, K, palette_transparents, max_colors=16):
    """
    blocks: lista di {bx,by,colors:dict(count), total_pixels}
    K: numero di palette richieste
    palette_transparents: lista di K colori RGB per la trasparenza
    Ritorna:
      palettes: list of dict {colors: Counter, blocks: [indices], transparent: rgb}
      block_assignments: list palette_index per blocco
    Strategia greedy:
      - ordina i blocchi per complessità (numero colori discend.)
      - per ciascun blocco prova ad inserirlo nella palette che dopo merge rimarrebbe <= max_colors (priorità palette con più similarità)
      - se nessuna palette può inserirlo, prova con merge più aggressivo (tol più alto)
      - se ancora niente, forza l'assegnazione alla palette con minima penalità, forzando merge distruttiva
    """

    # inizializza palette vuote con colore di trasparenza già presente
    palettes = []
    for i in range(K):
        p = {"colors": Counter(), "blocks": [], "transparent": palette_transparents[i]}
        # force transparent color in palette
        p["colors"][palette_transparents[i]] = 0
        palettes.append(p)

    block_assignments = [-1] * len(blocks)
    # indici blocchi ordinati per "difficoltà" (numero colori discend.)
    order = sorted(range(len(blocks)), key=lambda i: len(blocks[i]['colors']), reverse=True)

    for bi in order:
        blk = blocks[bi]
        blk_colors = Counter(blk['colors'])

        # candidate palette selection: compute "compatibility score" for each palette
        best_palette = None
        best_metric = None
        best_merged = None

        # prova inserimento con tolleranza progressiva
        for palette_index, pal in enumerate(palettes):
            # merged color set if we add blk
            merged = Counter(pal['colors']) + blk_colors
            # try reduce to max_colors
            success, reduced = try_reduce_colors(merged, fixed_colors=[pal['transparent']], max_colors=max_colors)
            if success:
                # metric: favor palette where fewer merges necessary => smaller len(reduced) and more overlap
                overlap = sum((Counter(pal['colors']) & blk_colors).values())
                metric = (len(reduced), -overlap)  # smaller better
                if best_metric is None or metric < best_metric:
                    best_metric = metric
                    best_palette = palette_index
                    best_merged = reduced

        if best_palette is not None:
            # assegna al best_palette
            palettes[best_palette]['colors'] = best_merged
            palettes[best_palette]['blocks'].append(bi)
            block_assignments[bi] = best_palette
            continue

        # se siamo qui, nessuna palette ha accettato il blocco con la strategia normale.
        # proviamo strategie più aggressive: aumentiamo tolleranza via try_reduce_colors già dentro
        forced_choice = None
        forced_score = None
        forced_reduced = None
        for palette_index, pal in enumerate(palettes):
            merged = Counter(pal['colors']) + blk_colors
            # try_reduce_colors ritorna False ma può comunque restituire un reduced parziale; proviamo con tol_max alto
            success, reduced = try_reduce_colors(merged, fixed_colors=[pal['transparent']], max_colors=max_colors, tol_start=30, tol_step=20, tol_max=400)
            if success:
                # accettiamo questa soluzione (anche se con tolleranza alta)
                forced_choice = palette_index
                forced_reduced = reduced
                break
            # altrimenti valutiamo quanto "dannosa" sarebbe forzare la riduzione:
            # metric: numero colori finali se forzassimo a forza (fuse tutti meno usati)
            # simuliamo "forza" rimuovendo i meno frequenti fino a max_colors, unendoli al nearest
            temp = Counter(merged)
            # while len>max -> force-merge least frequent into nearest (no tol limit)
            while len(temp) > max_colors:
                least, _ = min(temp.items(), key=lambda x: x[1])
                # find nearest remaining
                candidates = [(other, rgb_dist(least, other)) for other in temp.keys() if other != least]
                if not candidates:
                    break
                nearest, _ = min(candidates, key=lambda x: x[1])
                temp[nearest] += temp[least]
                del temp[least]
            score = len(temp)
            if forced_choice is None or score < forced_score:
                forced_choice = palette_index
                forced_score = score
                forced_reduced = temp

        # assegna forzatamente a forced_choice
        if forced_choice is None:
            # ultimo tentativo: append to palette 0 forcibly
            forced_choice = 0
            forced_reduced = Counter(palettes[0]['colors']) + blk_colors
            # force-squeeze to max_colors
            while len(forced_reduced) > max_colors:
                least, _ = min(forced_reduced.items(), key=lambda x: x[1])
                candidates = [(other, rgb_dist(least, other)) for other in forced_reduced.keys() if other != least]
                if not candidates:
                    break
                nearest, _ = min(candidates, key=lambda x: x[1])
                forced_reduced[nearest] += forced_reduced[least]
                del forced_reduced[least]

        palettes[forced_choice]['colors'] = forced_reduced
        palettes[forced_choice]['blocks'].append(bi)
        block_assignments[bi] = forced_choice

    # finito assegniamo indici/normalizzi palette (riempiamo fino a 16 colori)
    for p in palettes:
        # ensure fixed transparent color first
        items = list(p['colors'].items())
        # sort by frequency desc
        items_sorted = sorted(items, key=lambda t: -t[1])
        colors_only = [c for c, _ in items_sorted]
        # ensure transparent is first entry
        if p['transparent'] in colors_only:
            colors_only.remove(p['transparent'])
            colors_only.insert(0, p['transparent'])
        else:
            colors_only.insert(0, p['transparent'])
        # trim or pad to 16
        colors_only = colors_only[:max_colors]
        while len(colors_only) < max_colors:
            colors_only.append((0,0,0))
        p['final_colors'] = colors_only

    return palettes, block_assignments

# ---------- scrittura JASC-PAL ----------
def write_jasc_pal(path, colors_rgb_list):
    """
    colors_rgb_list: list of 16 (r,g,b) tuples
    Writes JASC-PAL file with header and 16 colors
    """
    with open(path, "w", encoding="utf-8") as f:
        f.write("JASC-PAL\n")
        f.write("0100\n")
        f.write("16\n")
        for (r,g,b) in colors_rgb_list:
            f.write(f"{r} {g} {b}\n")

# ---------- main CLI ----------
def main():
    parser = argparse.ArgumentParser(description="Ottimizza palette per tileset: suddivide in blocchi 8x8 e trova K palette da 16 colori.")
    parser.add_argument("input_image", help="Percorso immagine input (tileset)")
    parser.add_argument("-k", "--palettes", type=int, required=True, help="Numero di palette desiderate (K)")
    parser.add_argument("-t", "--transparent", nargs='+', required=True,
                        help="Lista dei colori di trasparenza in esadecimale (uno per palette), es: #FF00FF #000000 ...")
    parser.add_argument("-o", "--outdir", default="out_palettes", help="Cartella di output")
    parser.add_argument("--block-size", type=int, default=8, help="Dimensione del blocco (default 8)")
    parser.add_argument("--max-colors", type=int, default=16, help="Numero massimo colori per palette (default 16)")
    args = parser.parse_args()

    if len(args.transparent) != args.palettes:
        print("Errore: devi fornire esattamente tanti colori di trasparenza quanti sono le palette (K).", file=sys.stderr)
        sys.exit(1)

    os.makedirs(args.outdir, exist_ok=True)

    # parse transparency colors
    palette_trans = [hex_to_rgb(h) for h in args.transparent]

    img = Image.open(args.input_image)
    blocks, cols, rows = extract_blocks(img, block_size=args.block_size, ignore_transparent_colors=palette_trans)

    palettes, assignments = assign_blocks_to_palettes(blocks, args.palettes, palette_transparents=palette_trans, max_colors=args.max_colors)

    # write .pal files
    pal_paths = []
    for i, p in enumerate(palettes):
        pal_colors = p['final_colors']
        path = os.path.join(args.outdir, f"palette_{i}.pal")
        write_jasc_pal(path, pal_colors)
        pal_paths.append(path)

    # produce mapping JSON: per block -> palette index; and palette colors
    mapping = {
        "input_image": args.input_image,
        "block_size": args.block_size,
        "grid": {"cols": cols, "rows": rows},
        "palettes": [
            {
                "index": i,
                "transparent": palettes[i]['transparent'],
                "colors": palettes[i]['final_colors'],
                "num_blocks": len(palettes[i]['blocks'])
            } for i in range(len(palettes))
        ],
        "blocks": []
    }
    for idx, b in enumerate(blocks):
        mapping['blocks'].append({
            "index": idx,
            "bx": b['bx'],
            "by": b['by'],
            "assigned_palette": assignments[idx],
            "unique_colors": len(b['colors'])
        })

    mapping_path = os.path.join(args.outdir, "palettes_mapping.json")
    with open(mapping_path, "w", encoding="utf-8") as f:
        json.dump(mapping, f, indent=2)

    print(f"[OK] Palette generate in: {args.outdir}")
    for p in pal_paths:
        print(" -", p)
    print("[OK] Mapping JSON:", mapping_path)

if __name__ == "__main__":
    main()
