import sys
import re

def hex_to_rgb_lines(text: str):
    lines = []
    lines.append("JASC-PAL")
    lines.append("0100")
    lines.append("16")
    for token in re.findall(r'0x[0-9a-fA-F]{6,8}', text):
        val = int(token, 16)
        r = (val >> 16) & 0xFF
        g = (val >> 8) & 0xFF
        b = val & 0xFF
        lines.append(f"{r} {g} {b}")
    return "\n".join(lines)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Uso: python {sys.argv[0]} input.pal output.pal")
        sys.exit(1)

    input_file, output_file = sys.argv[1], sys.argv[2]

    with open(input_file, "r", encoding="utf-8") as f:
        data = f.read()

    rgb_text = hex_to_rgb_lines(data)

    with open(output_file, "w", encoding="utf-8") as f:
        f.write(rgb_text + "\n")
