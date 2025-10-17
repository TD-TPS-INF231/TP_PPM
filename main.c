#include <stdio.h>
#include<string.h>
#include <stdlib.h>

// Définition de la valeur maximale pour une composante de couleur 8 bits
#define MAX_VALEUR 255

// Structure pour représenter une couleur (un pixel)
typedef struct {
    unsigned char rouge;
    unsigned char vert;
    unsigned char bleu;
} Couleur;
typedef struct
{
    int hauteur;
    int largeur;
} Image;
typedef struct 
{
    int r;
    int g;
    int b;
}Pixel;
//prototypes fonctions
void creer_image();
void eclaircir_image();
Couleur creer_negatif(Couleur originale);
void creer_negatif_image();
void decouper_partie_image();
void Filtre_Median();

void creer_image()
{
    Image img;
    Pixel couleur;
    printf("entrer la largeur de l'image : ");
    scanf("%d", &img.largeur);
    getchar();
    printf("entrer la hauteur de l'image : ");
    scanf("%d", &img.hauteur);

    FILE *fichier = fopen("image.ppm", "w");
    if (fichier == NULL)
    {
        printf("Erreur lors de la création du fichier.\n");
        return;
    }
    fprintf(fichier, "P3\n%d %d\n255\n", img.largeur, img.hauteur);

    for (int i = img.hauteur - 1; i >= 0; i--)
    {
        for (int j = 0; j < img.largeur; j++)
        {
            float r = (float)j / (float)img.hauteur;
            float g = (float)i / (float)img.largeur;
            float b = 0.2;
            int ir = (int)(r * 255.99);
            int ig = (int)(g * 255.99);
            int ib = (int)(b * 255.99);

            couleur.r = ir;
            couleur.g = ig;
            couleur.b = ib;

            fprintf(fichier, "%d %d %d ", ir, ig, ib);
        }
        if(i > 0)
            fprintf(fichier, "\n");
    }
    fclose(fichier); 
    printf("Image générée et enregistrée dans 'image.ppm'\n");
}
void eclaircir_image() {
    char nom_sortie[100];
    int intensite;
    
    // Utilise directement l'image créée par creer_image()
    char* nom_entree = "image.ppm";
    
    printf("Entrer le nom du fichier résultat: ");
    scanf("%s", nom_sortie);
    printf("Entrer l'intensité d'éclaircissement (0-100): ");
    scanf("%d", &intensite);
    
    // Ouvrir les fichiers
    FILE *fichier_entree = fopen(nom_entree, "r");
    FILE *fichier_sortie = fopen(nom_sortie, "w");
    
    if (fichier_entree == NULL) {
        printf("Erreur: Le fichier 'image.ppm' n'existe pas\n");
        printf("Veuillez d'abord créer une image avec l'option 1\n");
        return;
    }
    
    if (fichier_sortie == NULL) {
        printf("Erreur: Impossible de créer le fichier %s\n", nom_sortie);
        fclose(fichier_entree);
        return;
    }
    
    // Lire l'en-tête PPM
    char format[3];
    int largeur, hauteur, valeur_max;
    fscanf(fichier_entree, "%s", format);
    fscanf(fichier_entree, "%d %d", &largeur, &hauteur);
    fscanf(fichier_entree, "%d", &valeur_max);
    
    // Vérifier le format
    if (strcmp(format, "P3") != 0) {
        printf("Erreur: Format PPM non supporté\n");
        fclose(fichier_entree);
        fclose(fichier_sortie);
        return;
    }
    
    // Écrire l'en-tête dans le fichier de sortie
    fprintf(fichier_sortie, "P3\n%d %d\n%d\n", largeur, hauteur, valeur_max);
    
    // Traiter chaque pixel
    int r, g, b;
    
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            // Lire les valeurs RGB
            fscanf(fichier_entree, "%d %d %d", &r, &g, &b);
            
            // Appliquer l'éclaircissement
            r = r + intensite;
            g = g + intensite;
            b = b + intensite;
            
            // Limiter les valeurs entre 0 et 255
            if (r > 255) r = 255;
            if (g > 255) g = 255;
            if (b > 255) b = 255;
            if (r < 0) r = 0;
            if (g < 0) g = 0;
            if (b < 0) b = 0;
            
            // Écrire les nouvelles valeurs
            fprintf(fichier_sortie, "%d %d %d ", r, g, b);
        }
        fprintf(fichier_sortie, "\n");
    }
    
    fclose(fichier_entree);
    fclose(fichier_sortie);
    
    printf("Image éclaircie avec succès!\n");
    printf("Fichier source: image.ppm (créé avec l'option 1)\n");
    printf("Fichier résultat: %s\n", nom_sortie);
    printf("Intensité appliquée: %d\n", intensite);
}

//  la fonction pour créer le négatif d'une image
Couleur creer_negatif(Couleur originale) {
    Couleur negatif;
    
    // Le négatif est calculé par : MAX_VALEUR - valeur_originale
    negatif.rouge = MAX_VALEUR - originale.rouge;
    negatif.vert  = MAX_VALEUR - originale.vert;
    negatif.bleu  = MAX_VALEUR - originale.bleu;
    Couleur couleur_originale = {200, 50, 100};
    Couleur couleur_negative = creer_negatif(couleur_originale);
    printf("--- Composantes Couleurs ---\n");
    printf("Originale (R, V, B) : (%u, %u, %u)\n", 
           couleur_originale.rouge, couleur_originale.vert, couleur_originale.bleu);
    printf("Négative (R, V, B) :  (%u, %u, %u)\n", 
           couleur_negative.rouge, couleur_negative.vert, couleur_negative.bleu);

    return 0;
}


// Fonction pour créer le négatif d'une image
void creer_negatif_image()
{
    char nom_fichier_entree[100];
    char nom_fichier_sortie[100];
    
    printf("Entrer le nom du fichier image source : ");
    scanf("%s", nom_fichier_entree);
    printf("Entrer le nom du fichier resultat : ");
    scanf("%s", nom_fichier_sortie);

    // Lire l'en-tête du fichier PPM
    char format[3];
    int largeur, hauteur, valeur_max;
    fscanf(fichier_entree, "%s", format);
    fscanf(fichier_entree, "%d %d", &largeur, &hauteur);
    fscanf(fichier_entree, "%d", &valeur_max);

    // Écrire l'en-tête dans le fichier de sortie
    fprintf(fichier_sortie, "%s\n", format);
    fprintf(fichier_sortie, "%d %d\n", largeur, hauteur);
    fprintf(fichier_sortie, "%d\n", valeur_max);

    // Traiter chaque pixel pour créer le négatif
    Pixel pixel_courant;
    for (int i = 0; i < hauteur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {
            fscanf(fichier_entree, "%d %d %d", &pixel_courant.r, &pixel_courant.g, &pixel_courant.b);
            
            // Calcul du négatif : soustraire de la valeur maximale
            pixel_courant.r = valeur_max - pixel_courant.r;
            pixel_courant.g = valeur_max - pixel_courant.g;
            pixel_courant.b = valeur_max - pixel_courant.b;
            
            fprintf(fichier_sortie, "%d %d %d ", pixel_courant.r, pixel_courant.g, pixel_courant.b);
        }
        fprintf(fichier_sortie, "\n");
    }

    fclose(fichier_entree);
    fclose(fichier_sortie);
    
    printf("Negatif cree avec succes dans : %s\n", nom_fichier_sortie);
}

void Filtre_Median()
{
    printf("Application du filtre median...\n");

    FILE *fichier_entree = fopen("image.ppm", "r");
    if (fichier_entree == NULL)
    {
        printf("Erreur: Impossible d'ouvrir image.ppm. Créez d'abord une image avec l'option 1.\n");
        return;
    }

    char format[3];
    int largeur, hauteur, max_val;
    fscanf(fichier_entree, "%2s", format);
    fscanf(fichier_entree, "%d %d", &largeur, &hauteur);
    fscanf(fichier_entree, "%d", &max_val);

    int ***pixels = (int ***)malloc(hauteur * sizeof(int **));
    for (int i = 0; i < hauteur; i++)
    {
        pixels[i] = (int **)malloc(largeur * sizeof(int *));
        for (int j = 0; j < largeur; j++)
        {
            pixels[i][j] = (int *)malloc(3 * sizeof(int));
            fscanf(fichier_entree, "%d %d %d", &pixels[i][j][0], &pixels[i][j][1], &pixels[i][j][2]);
        }
    }
    fclose(fichier_entree);

    FILE *fichier_sortie = fopen("image_median.ppm", "w");
    fprintf(fichier_sortie, "P3\n%d %d\n255\n", largeur, hauteur);

    for (int i = 0; i < hauteur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {
            int voisins_r[9], voisins_g[9], voisins_b[9];
            int count = 0;

            for (int ki = -1; ki <= 1; ki++)
            {
                for (int kj = -1; kj <= 1; kj++)
                {
                    int ni = i + ki;
                    int nj = j + kj;

                    if (ni >= 0 && ni < hauteur && nj >= 0 && nj < largeur)
                    {
                        voisins_r[count] = pixels[ni][nj][0];
                        voisins_g[count] = pixels[ni][nj][1];
                        voisins_b[count] = pixels[ni][nj][2];
                        count++;
                    }
                }
            }

            for (int k = 0; k < count - 1; k++)
            {
                for (int l = k + 1; l < count; l++)
                {
                    if (voisins_r[k] > voisins_r[l])
                    {
                        int temp = voisins_r[k];
                        voisins_r[k] = voisins_r[l];
                        voisins_r[l] = temp;
                    }
                    if (voisins_g[k] > voisins_g[l])
                    {
                        int temp = voisins_g[k];
                        voisins_g[k] = voisins_g[l];
                        voisins_g[l] = temp;
                    }
                    if (voisins_b[k] > voisins_b[l])
                    {
                        int temp = voisins_b[k];
                        voisins_b[k] = voisins_b[l];
                        voisins_b[l] = temp;
                    }
                }
            }

            // Écrire le pixel médian
            int median_r = voisins_r[count / 2];
            int median_g = voisins_g[count / 2];
            int median_b = voisins_b[count / 2];
            fprintf(fichier_sortie, "%d %d %d ", median_r, median_g, median_b);
        }
        fprintf(fichier_sortie, "\n");
    }

    fclose(fichier_sortie);

    for (int i = 0; i < hauteur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {
            free(pixels[i][j]);
        }
        free(pixels[i]);
    }
    free(pixels);

    printf("Filtre median appliqué avec succès! Resultat dans 'image_median.ppm'\n");
}

// Fonction pour découper une partie de l'image
void decouper_partie_image()
{
    char nom_fichier_entree[100];
    char nom_fichier_sortie[100];
    
    printf("Entrer le nom du fichier image source : ");
    scanf("%s", nom_fichier_entree);
    printf("Entrer le nom du fichier resultat : ");
    scanf("%s", nom_fichier_sortie);

    FILE *fichier_entree = fopen(nom_fichier_entree, "r");
    FILE *fichier_sortie = fopen(nom_fichier_sortie, "w");
    
    if (fichier_entree == NULL || fichier_sortie == NULL)
    {
        printf("Erreur : Impossible d'ouvrir les fichiers\n");
        return;
    }

    // Lire l'en-tête du fichier PPM
    char format[3];
    int largeur, hauteur, valeur_max;
    fscanf(fichier_entree, "%s", format);
    fscanf(fichier_entree, "%d %d", &largeur, &hauteur);
    fscanf(fichier_entree, "%d", &valeur_max);

    // Écrire l'en-tête dans le fichier de sortie
    fprintf(fichier_sortie, "%s\n", format);
    fprintf(fichier_sortie, "%d %d\n", largeur, hauteur);
    fprintf(fichier_sortie, "%d\n", valeur_max);

    // Traiter chaque pixel pour créer le négatif
    Pixel pixel_courant;
    for (int i = 0; i < hauteur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {
            fscanf(fichier_entree, "%d %d %d", &pixel_courant.r, &pixel_courant.g, &pixel_courant.b);
            
            // Calcul du négatif : soustraire de la valeur maximale
            pixel_courant.r = valeur_max - pixel_courant.r;
            pixel_courant.g = valeur_max - pixel_courant.g;
            pixel_courant.b = valeur_max - pixel_courant.b;
            
            fprintf(fichier_sortie, "%d %d %d ", pixel_courant.r, pixel_courant.g, pixel_courant.b);
        }
        fprintf(fichier_sortie, "\n");
    }

    fclose(fichier_entree);
    fclose(fichier_sortie);
    
    printf("Negatif cree avec succes dans : %s\n", nom_fichier_sortie);
}

    // Calculer les nouvelles dimensions
    int nouvelle_largeur = colonne_fin - colonne_debut + 1;
    int nouvelle_hauteur = ligne_fin - ligne_debut + 1;

    // Écrire le nouvel en-tête
    fprintf(fichier_sortie, "%s\n", format);
    fprintf(fichier_sortie, "%d %d\n", nouvelle_largeur, nouvelle_hauteur);
    fprintf(fichier_sortie, "%d\n", valeur_max);

    // Lire et écrire seulement la partie découpée
    Pixel pixel_courant;
    for (int ligne = 0; ligne < hauteur_originale; ligne++)
    {
        for (int colonne = 0; colonne < largeur_originale; colonne++)
        {
            fscanf(fichier_entree, "%d %d %d", &pixel_courant.r, &pixel_courant.g, &pixel_courant.b);
            
            // Si le pixel est dans la zone à découper, l'écrire
            if (ligne >= ligne_debut && ligne <= ligne_fin && 
                colonne >= colonne_debut && colonne <= colonne_fin)
            {
                fprintf(fichier_sortie, "%d %d %d ", pixel_courant.r, pixel_courant.g, pixel_courant.b);
            }
        }
    }

    fclose(fichier_entree);
    fclose(fichier_sortie);
    
    printf("Decoupage reussi ! Partie enregistree dans : %s\n", nom_fichier_sortie);
    printf("Nouvelle taille : %d x %d pixels\n", nouvelle_largeur, nouvelle_hauteur);
}

int main(int argc, char* argv[])

{
    int choix;
    do
    {
        printf("--Bienvenue dans la manipulation des images PPM--\n");
        printf("1.Afficher l'image utilisee\n");
        printf("2.Eclaircir les pixels\n");
        printf("3.Passer en noir et blanc \n");
        printf("4.Le negatif de l'image\n");
        printf("5.Afficher la taille de l'image\n");
        printf("6.Decouper et Afficher une partie de l'image\n");
        printf("7.filtre median\n");
        printf("0.Quitter\n");
        printf("Entrer votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            printf("voici l'image utiliser\n");
            creer_image();
            break;
        case 2:
        eclaircir_image();  // Utilise image.ppm créé précédemment
            break;
        case 3:
            printf("3.le negatif de l'image \n");
            break;
        case 5:
            printf("voici le négatif de l'image\n");
            creer_negatif_image();
            break;
        case 6:
            printf("voici votre image découper");
            decouper_partie_image();
            break;
            case 7:
            printf("Voici le filtre median\n");
            Filtre_Median();

        case 0:
            printf("Aurevoir\n");
            break;
        default:
            printf("choix indisponible\n");
            break;
        }
    } while (choix != 0);
    return 0;
}
