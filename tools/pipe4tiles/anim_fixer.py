from PIL import Image
import numpy as np
import os

def ricomponi_blocchi(input_path, output_folder):
    """
    Divide un'immagine in blocchi 16x8 disposti verticalmente e li ricompone
    in blocchi 16x16 separati. Il primo blocco va sotto il terzo, il secondo
    sotto il quarto, ecc.

    Args:
        input_path: percorso dell'immagine di input
        output_folder: cartella dove salvare i blocchi ricomposti
    """
    # Carica l'immagine
    img = Image.open(input_path)
    img_array = np.array(img)

    height, width = img_array.shape[:2]

    # Verifica che le dimensioni siano corrette
    if width != 16:
        raise ValueError(f"La larghezza dell'immagine deve essere 16 pixel, trovata: {width}")

    if height % 8 != 0:
        raise ValueError(f"L'altezza ({height}) deve essere multipla di 8")

    # Calcola il numero di blocchi 16x8
    n_blocchi = height // 8

    # Verifica che ci sia un numero pari di blocchi
    if n_blocchi % 2 != 0:
        raise ValueError(f"Il numero di blocchi ({n_blocchi}) deve essere pari per accoppiarli")

    # Crea la cartella di output se non esiste
    os.makedirs(output_folder, exist_ok=True)

    # Estrai i blocchi e ricomponili
    # n_coppie = n_blocchi // 2

    for i in range(0, n_blocchi, 2):
        # Indici dei blocchi da accoppiare
        # Coppia 0: blocco 0 (1°) va sotto blocco 2 (3°)
        # Coppia 1: blocco 1 (2°) va sotto blocco 3 (4°)
        # Coppia 2: blocco 4 (5°) va sotto blocco 6 (7°)
        # ecc.
        blocco_inferiore_idx = i              # 0, 1, 2, 3, ...
        blocco_superiore_idx = i + 1  # n_coppie, n_coppie+1, ...

        # Estrai i blocchi 16x8
        y_inf_start = blocco_inferiore_idx * 8
        y_inf_end = y_inf_start + 8
        blocco_inferiore = img_array[y_inf_start:y_inf_end, :]

        y_sup_start = blocco_superiore_idx * 8
        y_sup_end = y_sup_start + 8
        blocco_superiore = img_array[y_sup_start:y_sup_end, :]

        # Crea il blocco 16x16 ricomposto
        # Il blocco superiore (es. 3°) va sopra
        # Il blocco inferiore (es. 1°) va sotto
        blocco_16x16 = np.vstack([blocco_inferiore, blocco_superiore])

        # Salva come immagine separata
        output_img = Image.fromarray(blocco_16x16)
        output_filename = os.path.join(output_folder, f"blocco_{i:03d}.png")
        output_img.save(output_filename)

        print(f"Salvato {output_filename}: blocco {blocco_superiore_idx+1} sopra, blocco {blocco_inferiore_idx+1} sotto")

    print(f"\nCompletato! Creati {n_blocchi / 2} blocchi 16x16 in '{output_folder}'")
    print(f"Blocchi originali: {n_blocchi} (16x8)")
    print(f"Blocchi ricomposti: {n_blocchi / 2} (16x16)")

# Esempio di utilizzo
if __name__ == "__main__":
    # Modifica questi percorsi con i tuoi file
    input_image = "waterfall_frame3.png"
    output_folder = "waterfall/frame3"

    try:
        ricomponi_blocchi(input_image, output_folder)
    except Exception as e:
        print(f"Errore: {e}")