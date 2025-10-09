#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

.
#pragma pack(push, 1)

typedef struct {
    uint16_t bfType;      // Signature 'BM' (0x4D42)
    uint32_t bfSize;      // Taille totale du fichier
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;   
} BMPFileHeader;

typedef struct {
    uint32_t biSize;          // Taille de ce header (40)
    int32_t  biWidth;         // Largeur
    int32_t  biHeight;        // Hauteur
    uint16_t biPlanes;
    uint16_t biBitCount;      // Bits par pixel (doit être 24 ici)
    uint32_t biCompression;   // Doit être 0
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BMPInfoHeader;


typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} Pixel;

#pragma pack(pop)

// --- 2. Fonction de Filtre ---

/**
 * Applique le filtre négatif à l'image.
 * Pour chaque composante de couleur (R, G, B), calcule 255 - valeur_actuelle.
 */
void applyNegativeFilter(Pixel* pixels, int width, int height) {
    if (!pixels) return;

    long total_pixels = (long)width * height;

    for (long i = 0; i < total_pixels; ++i) {
        // Négatif pour la composante Bleue
        pixels[i].blue = 255 - pixels[i].blue;
        
        // Négatif pour la composante Verte
        pixels[i].green = 255 - pixels[i].green;
        
        // Négatif pour la composante Rouge
        pixels[i].red = 255 - pixels[i].red;
    }
}

// --- 3. Fonctions Utilitaire (Lecture/Écriture) ---

Pixel* loadImageBMP(const char* filename, BMPFileHeader* fileHeader, BMPInfoHeader* infoHeader);
void saveImageBMP(const char* filename, const BMPFileHeader* fileHeader, const BMPInfoHeader* infoHeader, const Pixel* pixels);

// NOTE: Le corps des fonctions loadImageBMP et saveImageBMP est omis ici pour la concision, 
// mais il doit être le même que dans la réponse précédente pour gérer les headers et le padding.

// --- 4. Fonction Principale (main) ---
int main() {
    const char* INPUT_FILE = "input.bmp";
    const char* OUTPUT_FILE = "output_negative.bmp";

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    Pixel* pixels = NULL;

    printf("--- Programme de création de négatif d'image ---\n");
    
    // 1. Chargement de l'image (Assurez-vous que cette fonction est bien définie)
    pixels = loadImageBMP(INPUT_FILE, &fileHeader, &infoHeader);

    if (pixels == NULL) {
        fprintf(stderr, "Échec du chargement de l'image ou format non supporté.\n");
        return 1;
    }

    printf("Image chargée : %d x %d pixels.\n", infoHeader.biWidth, infoHeader.biHeight);

    // 2. Application du filtre
    printf("Application du filtre négatif...\n");
    applyNegativeFilter(pixels, infoHeader.biWidth, infoHeader.biHeight);

    // 3. Sauvegarde de l'image
    saveImageBMP(OUTPUT_FILE, &fileHeader, &infoHeader, pixels);

    printf("Image négative enregistrée sous '%s'.\n", OUTPUT_FILE);
    
    // 4. Nettoyage de la mémoire
    free(pixels); 
    
    return 0;
}
