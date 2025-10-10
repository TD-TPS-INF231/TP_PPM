#include <stdio.h>
#include<string.h>
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
// Fonction pour créer le négatif d'une image
void creer_negatif_image()
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

// Fonction pour découper une partie de l'image
void decouper_partie_image()
{
    char nom_fichier_entree[100];
    char nom_fichier_sortie[100];
    int ligne_debut, ligne_fin, colonne_debut, colonne_fin;
    
    printf("Entrer le nom du fichier image source : ");
    scanf("%s", nom_fichier_entree);
    printf("Entrer la ligne de debut : ");
    scanf("%d", &ligne_debut);
    printf("Entrer la ligne de fin : ");
    scanf("%d", &ligne_fin);
    printf("Entrer la colonne de debut : ");
    scanf("%d", &colonne_debut);
    printf("Entrer la colonne de fin : ");
    scanf("%d", &colonne_fin);
    printf("Entrer le nom du fichier resultat : ");
    scanf("%s", nom_fichier_sortie);

    FILE *fichier_entree = fopen(nom_fichier_entree, "r");
    FILE *fichier_sortie = fopen(nom_fichier_sortie, "w");
    
    if (fichier_entree == NULL || fichier_sortie == NULL)
    {
        printf("Erreur : Impossible d'ouvrir les fichiers\n");
        return;
    }

    // Lire l'en-tête
    char format[3];
    int largeur_originale, hauteur_originale, valeur_max;
    fscanf(fichier_entree, "%s", format);
    fscanf(fichier_entree, "%d %d", &largeur_originale, &hauteur_originale);
    fscanf(fichier_entree, "%d", &valeur_max);

    // Vérifier que les coordonnées de découpage sont valides
    if (ligne_debut < 0 || ligne_fin >= hauteur_originale || 
        colonne_debut < 0 || colonne_fin >= largeur_originale ||
        ligne_debut > ligne_fin || colonne_debut > colonne_fin)
    {
        printf("Erreur : Coordonnees de decoupage invalides\n");
        fclose(fichier_entree);
        fclose(fichier_sortie);
        return;
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
