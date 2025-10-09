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

            fprintf(fichier, "%d %d %d ", ir, ig, ib);
        }
        if(i > 0)
            fprintf(fichier, "\n");
    }
    fclose(fichier); 
    printf("Image générée et enregistrée dans 'image.ppm'\n");
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
        default:
            printf("choix indisponible\n");
            break;
        }
    } while (choix != 0);
    return 0;
}
