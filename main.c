#include <stdio.h>

#include <stdlib.h>

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

//prototypes des fonctions
void creer_image();
void filtre_median(Pixel tab[], int n);

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

void filtre_median (Pixel tab[], int n){

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

int main()
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
            case 7:
            printf("Voici le filtre median\n");
            Filtre_Median();
            break;
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
