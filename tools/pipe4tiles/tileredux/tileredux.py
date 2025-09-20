# utility to deduplicate 8x8 sections (allowing X/Y flips), compact them and produce mapping JSON + atlas PNG
import argparse
from PIL import Image, ImageOps
import json, os, math

def process_tileset(img: Image.Image, block_size=8, out_prefix="output/", filename="tileset"):
    img = img.convert("RGBA")
    w, h = img.size
    if w % block_size != 0 or h % block_size != 0:
        raise ValueError(f"Image size {w}x{h} is not multiple of block size {block_size}")
    cols = w // block_size
    rows = h // block_size

    # extract blocks
    blocks = []
    for by in range(rows):
        for bx in range(cols):
            left = bx * block_size
            top = by * block_size
            block = img.crop((left, top, left + block_size, top + block_size))
            blocks.append({"bx": bx, "by": by, "img": block})

    def variants_bytes(block_img):
        v = {}
        v["none"] = block_img.tobytes()
        fx = ImageOps.mirror(block_img)
        fy = ImageOps.flip(block_img)
        fx_fy = ImageOps.flip(fx)
        v["fx"] = fx.tobytes()
        v["fy"] = fy.tobytes()
        v["fxfy"] = fx_fy.tobytes()
        return v

    unique_images = []
    unique_bytes = []
    block_mappings = []
    unique_first_pos = {}

    for idx, blk in enumerate(blocks):
        img_blk = blk["img"]
        variants = variants_bytes(img_blk)
        found = False
        for uid, ubytes in enumerate(unique_bytes):
            if ubytes == variants["none"]:
                block_mappings.append({"unique_id": uid, "flip_x": False, "flip_y": False})
                found = True; break
            if ubytes == variants["fx"]:
                block_mappings.append({"unique_id": uid, "flip_x": True, "flip_y": False})
                found = True; break
            if ubytes == variants["fy"]:
                block_mappings.append({"unique_id": uid, "flip_x": False, "flip_y": True})
                found = True; break
            if ubytes == variants["fxfy"]:
                block_mappings.append({"unique_id": uid, "flip_x": True, "flip_y": True})
                found = True; break
        if not found:
            uid = len(unique_images)
            unique_images.append(img_blk.copy())
            unique_bytes.append(variants["none"])
            block_mappings.append({"unique_id": uid, "flip_x": False, "flip_y": False})
            unique_first_pos[uid] = idx

    num_unique = len(unique_images)
    fixed_width = 128
    cols = fixed_width // block_size
    comp_rows = math.ceil(num_unique / cols)
    atlas_w = fixed_width
    atlas_h = comp_rows * block_size
    atlas = Image.new("RGBA", (atlas_w, atlas_h), (0, 0, 0, 0))

    ordered_uids = sorted(range(num_unique), key=lambda u: unique_first_pos[u])
    uid_to_placement = {uid: pos for pos, uid in enumerate(ordered_uids)}

    for uid, pos in uid_to_placement.items():
        px = (pos % cols) * block_size
        py = (pos // cols) * block_size
        atlas.paste(unique_images[uid], (px, py))

    blocks_info = []
    for idx, blk in enumerate(blocks):
        mapping = block_mappings[idx]
        uid = mapping["unique_id"]
        placement = uid_to_placement[uid]
        p_bx = placement % cols
        p_by = placement // cols
        blocks_info.append({
            "orig_bx": blk["bx"],
            "orig_by": blk["by"],
            "atlas_bx": p_bx,
            "atlas_by": p_by,
            "unique_id": uid,
            "flip_x": mapping["flip_x"],
            "flip_y": mapping["flip_y"]
        })

    os.makedirs(os.path.dirname(out_prefix+"/"), exist_ok=True)
    out_name = filename.replace(".png", "")
    atlas_path = f"{out_prefix}/{out_name}_atlas.png"
    json_path = f"{out_prefix}/{out_name}_map.json"
    atlas.save(atlas_path)

    mapping_json = {
        "original_image": {"width": w, "height": h},
        "block_size": block_size,
        "grid": {"cols": cols, "rows": rows},
        "atlas": {"path": os.path.basename(atlas_path), "width": atlas_w, "height": atlas_h, "cols": cols, "rows": comp_rows},
        "unique_count": num_unique,
        "unique_order": ordered_uids,
        "blocks": blocks_info
    }
    with open(json_path, "w", encoding="utf-8") as f:
        json.dump(mapping_json, f, indent=2)
    return atlas_path, json_path, mapping_json, atlas

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Deduplica blocchi 8x8 (o altra dimensione) da un'immagine pixel-art e genera atlas + mapping JSON."
    )
    parser.add_argument("input", help="Percorso dell'immagine di input (es. tileset.png)")
    parser.add_argument(
        "-b", "--block-size", type=int, default=8,
        help="Dimensione del blocco (default: 8)"
    )
    parser.add_argument(
        "-o", "--out-prefix", default="output",
        help="Prefisso file di output (default: tileset_output)"
    )
    args = parser.parse_args()

    img = Image.open(args.input)
    atlas_path, json_path, mapping_json, atlas_img = process_tileset(
        img, block_size=args.block_size, out_prefix=args.out_prefix, filename=args.input
    )

    print(f"[OK] Atlas salvato in: {atlas_path}")
    print(f"[OK] Mapping JSON salvato in: {json_path}")
    print(f"Blocchi unici trovati: {mapping_json['unique_count']}")