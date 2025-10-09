#include <stdio.h>

#include <stdlib.h>

typedef struct
{
    int hauteur;
    int largeur;
} Image;

void creer_image()
{
    Image img;
    int r, g, b;
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
    fprintf(fichier, "p3\n%d %d\n255\n", img.largeur, img.hauteur);

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

            fprintf(fichier, "%d %d  %d", ir, ig, ib);
        }
        if(i > 0)
            fprintf(fichier, "\n"); 
    }
    fclose(fichier); 
    printf("Image générée et enregistrée dans 'image.ppm'\n");
}
void noir_et_blanc()
{
    FILE *fichier = fopen("image.ppm", "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    char format[3];
    int largeur, hauteur, maxval;

    fscanf(fichier, "%s", format);
    fscanf(fichier, "%d %d", &largeur, &hauteur);
    fscanf(fichier, "%d", &maxval);

    FILE *fichier_nb = fopen("image_nb.ppm", "w");
    if (fichier_nb == NULL)
    {
        printf("Erreur lors de la création du fichier noir et blanc.\n");
        fclose(fichier);
        return;
    }

    fprintf(fichier_nb, "P3\n%d %d\n%d\n", largeur, hauteur, maxval);

    for (int i = 0; i < hauteur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {
            int r, g, b;
            fscanf(fichier, "%d %d %d", &r, &g, &b);
            int gray = (r + g + b) / 3;
            fprintf(fichier_nb, "%d %d %d ", gray, gray, gray);
        }
        fprintf(fichier_nb, "\n");
    }

    fclose(fichier);
    fclose(fichier_nb);
    printf("Image noir et blanc générée et enregistrée dans 'image_nb.ppm'\n");
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
        case 0:
            printf("Aurevoir\n");
            break;
        case 3:
            printf("noir et blanc\n");
            noir_et_blanc();
            break;
        default:
            printf("choix indisponible\n");
            break;
        }
    } while (choix != 0);
    return 0;
}
