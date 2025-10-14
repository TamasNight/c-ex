#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
patch_object_events.py
Versione tollerante, senza backup (.bak).
Modifica i file C secondo le regole definite.
"""

import argparse
import re
from pathlib import Path

# File paths
FILES = {
    "object_event_graphics_h": Path("../src/data/object_events/object_event_graphics.h"),
    "graphics_h": Path("../include/graphics.h"),
    "pic_tables_h": Path("../src/data/object_events/object_event_pic_tables.h"),
    "graphics_info_h": Path("../src/data/object_events/object_event_graphics_info.h"),
    "graphics_info_pointers_h": Path("../src/data/object_events/object_event_graphics_info_pointers.h"),
    "constants_event_objects_h": Path("../include/constants/event_objects.h"),
    "event_object_movement_c": Path("../src/event_object_movement.c"),
    "spritesheet_rules_mk": Path("../spritesheet_rules.mk"),
}

def read_lines(path: Path):
    if not path.exists():
        print(f"[WARN] File not found: {path}")
        return []
    return path.read_text(encoding="utf-8").splitlines()

def write_lines(path: Path, lines):
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"[INFO] Updated: {path}")

def ensure_not_present(lines, pattern):
    return not any(pattern in l for l in lines)

def insert_after_marker(lines, marker, new_lines):
    for i, l in enumerate(lines):
        if marker in l:
            if any(new_lines[0].strip() == existing.strip() for existing in lines[i+1:i+1+len(new_lines)]):
                print(f"[SKIP] Block already present after '{marker}'")
                return lines
            return lines[:i+1] + new_lines + lines[i+1:]
    print(f"[WARN] Marker not found: {marker}")
    return lines

def append_if_missing(lines, first_line, block_lines):
    if any(first_line in l for l in lines):
        print(f"[SKIP] Block starting with '{first_line}' already present")
        return lines
    return lines + [""] + block_lines

def main():
    p = argparse.ArgumentParser()
    p.add_argument("--img", required=True, help="nome base immagine (minuscolo)")
    args = p.parse_args()
    img = args.img
    Img = img.capitalize()
    IMG = img.upper()

    # --- 1) object_event_graphics.h ---
    path = FILES["object_event_graphics_h"]
    lines = read_lines(path)
    if lines:
        add_lines = [
            f'const u16 gObjectEventPal_{Img}[] = INCBIN_U16("graphics/object_events/pics/peoplemedieval/palettes/{img}.gbapal");',
            f'const u32 gObjectEventPic_{Img}[] = INCBIN_U32("graphics/object_events/pics/peoplemedieval/{img}.4bpp");'
        ]
        if ensure_not_present(lines, add_lines[0]):
            lines = append_if_missing(lines, add_lines[0], add_lines)
            write_lines(path, lines)

    # --- 2) graphics.h ---
    path = FILES["graphics_h"]
    lines = read_lines(path)
    if lines:
        lines = insert_after_marker(lines, "// Medieval - Tamas Class System", [f'extern const u16 gObjectEventPal_{Img}[];'])
        write_lines(path, lines)

    # --- 3) object_event_pic_tables.h ---
    path = FILES["pic_tables_h"]
    lines = read_lines(path)
    if lines:
        block = [
            f'static const struct SpriteFrameImage sPicTable_{Img}[] = {{',
            f'        overworld_ascending_frames(gObjectEventPic_{Img}, 2, 4),',
            f'}};'
        ]
        if ensure_not_present(lines, block[0]):
            lines = append_if_missing(lines, block[0], block)
            write_lines(path, lines)

    # --- 4) object_event_graphics_info.h ---
    path = FILES["graphics_info_h"]
    lines = read_lines(path)
    if lines:
        block = [
            f'const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_{Img} = {{',
            f'        .tileTag = TAG_NONE,',
            f'        .paletteTag = OBJ_EVENT_PAL_TAG_{IMG},',
            f'        .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,',
            f'        .size = 256,',
            f'        .width = 16,',
            f'        .height = 32,',
            f'        .paletteSlot = 0,',
            f'        .shadowSize = SHADOW_SIZE_M,',
            f'        .inanimate = FALSE,',
            f'        .compressed = FALSE,',
            f'        .tracks = TRACKS_FOOT,',
            f'        .oam = &gObjectEventBaseOam_16x32,',
            f'        .subspriteTables = sOamTables_16x32,',
            f'        .anims = sAnimTable_Standard,',
            f'        .images = sPicTable_{Img},',
            f'        .affineAnims = gDummySpriteAffineAnimTable,',
            f'}};'
        ]
        if ensure_not_present(lines, block[0]):
            lines = append_if_missing(lines, block[0], block)
            write_lines(path, lines)

    # --- 5) object_event_graphics_info_pointers.h ---
    path = FILES["graphics_info_pointers_h"]
    lines = read_lines(path)
    if lines:
        lines = insert_after_marker(lines, "// Medieval - Tamas Class System",
                                    [f'extern const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_{Img};'])
        # Inserisci nuova entry nell'array
        arr_start_re = re.compile(r'gObjectEventGraphicsInfoPointers\s*\[.*\]\s*=\s*\{')
        start_idx = next((i for i, l in enumerate(lines) if arr_start_re.search(l)), None)
        if start_idx is not None:
            end_idx = next((j for j in range(start_idx+1, len(lines)) if lines[j].strip() == '};'), None)
            if end_idx:
                new_entry = f'[OBJ_EVENT_GFX_{IMG}]  =            &gObjectEventGraphicsInfo_{Img},'
                if not any(new_entry.strip() == ln.strip() for ln in lines[start_idx:end_idx]):
                    lines.insert(end_idx, f'    {new_entry}')
                    print(f"[INFO] Added entry in gObjectEventGraphicsInfoPointers for {IMG}")
        write_lines(path, lines)

    # --- 6) constants/event_objects.h ---
    path = FILES["constants_event_objects_h"]
    lines = read_lines(path)
    if lines:
        # Trova #if OW_FOLLOWERS_POKEBALLS
        follower_idx = next((i for i, l in enumerate(lines) if "#if" in l and "OW_FOLLOWERS_POKEBALLS" in l), None)
        if follower_idx:
            # Cerca prima "0x" risalendo le righe
            hex_idx = None
            hex_val = None
            for i in range(follower_idx - 1, -1, -1):
                if "0x" in lines[i]:
                    m = re.search(r'0x[0-9A-Fa-f]+', lines[i])
                    if m:
                        hex_val = m.group(0)
                        hex_idx = i
                        break
            if hex_val:
                val = int(hex_val, 16)
                new_val = f"0x{val + 1:04X}"
                new_line = f"#define OBJ_EVENT_PAL_TAG_{IMG}            {new_val}"
                if new_line not in lines:
                    lines.insert(hex_idx + 1, new_line)
                    print(f"[INFO] Added OBJ_EVENT_PAL_TAG_{IMG} = {new_val}")
            else:
                print("[WARN] Nessuna definizione esadecimale trovata prima di OW_FOLLOWERS_POKEBALLS")

            # Gestisci NUM_OBJ_EVENT_GFX
            num_idx = next((i for i, l in enumerate(lines) if l.strip().startswith("#define NUM_OBJ_EVENT_GFX")), None)
            if num_idx is not None:
                m = re.search(r'#define\s+NUM_OBJ_EVENT_GFX\s+(\d+)', lines[num_idx])
                if m:
                    orig = int(m.group(1))
                    new_num = orig + 1
                    lines[num_idx] = f"#define NUM_OBJ_EVENT_GFX {new_num}"
                    new_define = f"#define OBJ_EVENT_GFX_{IMG}               {orig}"
                    insert_before = max(0, num_idx - 4)
                    if new_define not in lines:
                        lines.insert(insert_before, new_define)
                        print(f"[INFO] Added OBJ_EVENT_GFX_{IMG} = {orig}")
                    print(f"[INFO] Incremented NUM_OBJ_EVENT_GFX to {new_num}")
        write_lines(path, lines)

    # --- 7) event_object_movement.c ---
    path = FILES["event_object_movement_c"]
    lines = read_lines(path)
    if lines:
        insert_line = f'    {{gObjectEventPal_{Img},          OBJ_EVENT_PAL_TAG_{IMG}}},'
        marker = "#if OW_FOLLOWERS_POKEBALLS"
        for i, l in enumerate(lines):
            if marker in l:
                if not any(insert_line.strip() == ln.strip() for ln in lines[max(0, i-5):i]):
                    lines.insert(i, insert_line)
                    print(f"[INFO] Inserted palette entry before {marker}")
                break
        write_lines(path, lines)

    # --- 8) spritesheet_rules.mk ---
    path = FILES["spritesheet_rules_mk"]
    lines = read_lines(path)
    if lines:
        block = [
            f'$(OBJEVENTGFXDIR)/peoplemedieval/{img}.4bpp: %.4bpp: %.png ',
            f'\t$(GFX) $< $@ -mwidth 2 -mheight 4'
        ]
        lines = insert_after_marker(lines, "# Medieval - Tamas Class System", block)
        write_lines(path, lines)

    print("\n[DONE] Tutte le modifiche applicate.")

if __name__ == "__main__":
    main()
