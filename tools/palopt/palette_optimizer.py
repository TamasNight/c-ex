#!/usr/bin/env python3
"""
palette_optimizer.py
Ottimizza K palette da 16 colori per un tileset suddiviso in blocchi 8x8.
Genera K file .pal (JASC-PAL), un JSON di mapping e l'immagine modificata.
"""

from PIL import Image
import argparse, os, json, math
from collections import Counter
import sys


# ---------- utility colore ----------
def hex_to_rgb(h):
    h = h.lstrip('#')
    return tuple(int(h[i:i + 2], 16) for i in (0, 2, 4))


def rgb_dist(a, b):
    return (a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2 + (a[2] - b[2]) ** 2


# ---------- estrazione blocchi 8x8 ----------
def extract_blocks(img, block_size=8, ignore_transparent_colors=None):
    img = img.convert("RGBA")
    w, h = img.size
    cols, rows = w // block_size, h // block_size
    blocks = []
    for by in range(rows):
        for bx in range(cols):
            left, top = bx * block_size, by * block_size
            block = img.crop((left, top, left + block_size, top + block_size))
            pixels = list(block.getdata())
            cnt = Counter()
            for px in pixels:
                if len(px) == 4 and px[3] == 0:
                    continue
                rgb = px[:3]
                if ignore_transparent_colors and rgb in ignore_transparent_colors:
                    continue
                cnt[rgb] += 1
            blocks.append({
                "bx": bx, "by": by,
                "colors": dict(cnt),
                "total_pixels": sum(cnt.values())
            })
    return blocks, cols, rows


# ---------- merging con remap ----------
def reduce_with_remap(color_counter, fixed_colors, max_colors=16, tol=64):
    """
    Ritorna (Counter ridotto, dict remap{old->new})
    - Non sostituisce mai altri colori con il colore di trasparenza
    """
    c = Counter(color_counter)
    for fc in fixed_colors:
        if fc not in c:
            c[fc] = 0
    remap = {col: col for col in c.keys()}

    while len(c) > max_colors:
        # trova il meno frequente che non sia un colore fisso
        col, _ = min(((k,v) for k,v in c.items() if k not in fixed_colors), key=lambda x: x[1])

        # trova il candidato più vicino che NON sia trasparente
        candidates = [(other, rgb_dist(col, other))
                      for other in c.keys() if other != col and other not in fixed_colors]
        if not candidates:
            # se rimangono solo fissi, ci fermiamo
            break
        nearest, dist = min(candidates, key=lambda x: x[1])

        # unisci
        c[nearest] += c[col]
        del c[col]

        # aggiorna remap
        for k,v in list(remap.items()):
            if v == col:
                remap[k] = nearest

    return c, remap


# ---------- assegnazione blocchi ----------
def assign_and_recolor(img, blocks, cols, rows, K, palette_transparents, block_size=8, max_colors=16):
    palettes = [{"colors": Counter({palette_transparents[i]: 0}),
                 "blocks": [], "transparent": palette_transparents[i]}
                for i in range(K)]
    block_assignments = [-1] * len(blocks)
    pixels = img.load()

    for bi, blk in enumerate(blocks):
        blk_colors = Counter(blk['colors'])

        # scegli la palette che riesce a includere il blocco con meno nuovi colori
        best_choice, best_reduced, best_remap = None, None, None
        for pi, pal in enumerate(palettes):
            merged = Counter(pal['colors']) + blk_colors
            reduced, remap = reduce_with_remap(merged, [pal['transparent']], max_colors)
            if len(reduced) <= max_colors:
                if best_choice is None or len(reduced) < len(best_reduced):
                    best_choice, best_reduced, best_remap = pi, reduced, remap

        if best_choice is None:
            # se nessuna palette ci sta, forziamo nella prima
            best_choice = 0
            merged = Counter(palettes[0]['colors']) + blk_colors
            reduced, remap = reduce_with_remap(merged, [palettes[0]['transparent']], max_colors)
            best_reduced, best_remap = reduced, remap

        # aggiorna palette
        palettes[best_choice]['colors'] = best_reduced
        palettes[best_choice]['blocks'].append(bi)
        block_assignments[bi] = best_choice

        # applica remap ai pixel del blocco
        bx, by = blk["bx"], blk["by"]
        for y in range(by * block_size, (by + 1) * block_size):
            for x in range(bx * block_size, (bx + 1) * block_size):
                r, g, b, a = pixels[x, y]
                if a == 0: continue
                rgb = (r, g, b)
                if rgb in best_remap:
                    nr, ng, nb = best_remap[rgb]
                    pixels[x, y] = (nr, ng, nb, a)

    # normalizza palette a 16 colori
    for p in palettes:
        colors_only = list(p["colors"].keys())
        if p["transparent"] in colors_only:
            colors_only.remove(p["transparent"])
        colors_only = [p["transparent"]] + colors_only[:max_colors - 1]
        while len(colors_only) < max_colors:
            colors_only.append((0, 0, 0))
        p["final_colors"] = colors_only

    return palettes, block_assignments, img


# ---------- scrittura ----------
def write_jasc_pal(path, colors):
    with open(path, "w") as f:
        f.write("JASC-PAL\n0100\n16\n")
        for r, g, b in colors:
            f.write(f"{r} {g} {b}\n")


# ---------- main ----------
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("input_image")
    ap.add_argument("-k", "--palettes", type=int, required=True)
    ap.add_argument("-t", "--transparent", nargs="+", required=True,
                    help="Colori trasparenti in esadecimale (uno per palette)")
    ap.add_argument("-o", "--outdir", default="tiles")
    ap.add_argument("--block-size", type=int, default=8)
    ap.add_argument("--max-colors", type=int, default=16)
    args = ap.parse_args()

    if len(args.transparent) != args.palettes:
        sys.exit("Numero di colori trasparenti diverso da numero palette")

    os.makedirs(args.outdir, exist_ok=True)
    trans = [hex_to_rgb(c) for c in args.transparent]

    img = Image.open(args.input_image).convert("RGBA")
    blocks, cols, rows = extract_blocks(img, args.block_size, ignore_transparent_colors=trans)
    palettes, assignments, new_img = assign_and_recolor(img, blocks, cols, rows, args.palettes,
                                                        trans, block_size=args.block_size,
                                                        max_colors=args.max_colors)

    # salva palette
    for i, p in enumerate(palettes):
        path = os.path.join(args.outdir, f"palette_{i}.pal")
        write_jasc_pal(path, p["final_colors"])

    # salva immagine modificata
    out_img = os.path.join(args.outdir, "tiles.png")
    new_img.save(out_img)

    # salva mapping
    mapping = {
        "grid": {"cols": cols, "rows": rows},
        "block_size": args.block_size,
        "palettes": [{"index": i, "transparent": p["transparent"], "colors": p["final_colors"]}
                     for i, p in enumerate(palettes)],
        "blocks": [{"index": i, "bx": b["bx"], "by": b["by"], "palette": assignments[i]}
                   for i, b in enumerate(blocks)]
    }
    with open(os.path.join(args.outdir, "palettes_mapping.json"), "w") as f:
        json.dump(mapping, f, indent=2)

    print(f"[OK] Salvato tutto in {args.outdir}")


if __name__ == "__main__":
    main()
