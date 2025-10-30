#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NB_VIES 6
#define MAX_MOT 50

// Dessins du pendu
const char* PENDU[] = {
    "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n",
    "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n",
    "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n",
    "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n"
};

int main(void) {
    srand((unsigned int)time(NULL));

    char* mots[] = {
        "voiture", "ordinateur", "programmation", "pendu", "maison",
        "chocolat", "elephant", "aventure", "mystere", "galaxie"
    };
    int nombreDeMots = sizeof(mots) / sizeof(mots[0]);
    char motADeviner[MAX_MOT];
    int choix;

    printf("=== JEU DU PENDU ===\n\n");
    printf("1. Choisir un mot manuellement\n");
    printf("2. Mot choisi au hasard\n");
    printf("Votre choix : ");
    scanf_s("%d", &choix);
    getchar(); // Nettoyer le \n restant dans le buffer

    if (choix == 1) {
        printf("\nEntrez le mot à deviner : ");
        fgets(motADeviner, MAX_MOT, stdin);
        motADeviner[strcspn(motADeviner, "\n")] = '\0'; // Supprimer le retour ligne
        system("cls||clear"); // Effacer l’écran pour cacher le mot
    }
    else {
        // Copie manuelle du mot choisi aléatoirement
        int index = rand() % nombreDeMots;
        int i = 0;
        while (mots[index][i] != '\0' && i < MAX_MOT - 1) {
            motADeviner[i] = mots[index][i];
            i++;
        }
        motADeviner[i] = '\0';
    }

    int longueurMot = (int)strlen(motADeviner);
    char motCache[MAX_MOT];
    for (int i = 0; i < longueurMot; i++) motCache[i] = '_';
    motCache[longueurMot] = '\0';

    int vies = NB_VIES;
    int victoire = 0;
    char lettre;

    while (vies > 0 && !victoire) {
        printf("%s\n", PENDU[NB_VIES - vies]);
        printf("Mot : %s\n", motCache);
        printf("Vies restantes : %d\n", vies);
        printf("Propose une lettre : ");
        scanf_s(" %c", &lettre);

        int trouve = 0;
        for (int i = 0; i < longueurMot; i++) {
            if (motADeviner[i] == lettre && motCache[i] == '_') {
                motCache[i] = lettre;
                trouve = 1;
            }
        }

        if (!trouve) {
            vies--;
            printf("\nMauvaise lettre.\n");
        }
        else {
            printf("\nBonne lettre.\n");
        }

        if (strcmp(motCache, motADeviner) == 0)
            victoire = 1;

        printf("\n");
    }

    printf("%s\n", PENDU[NB_VIES - vies]);
    if (victoire)
        printf("Bravo ! Tu as trouvé le mot : %s\n", motADeviner);
    else
        printf("Dommage... Le mot était : %s\n", motADeviner);

    printf("\nAppuie sur Entrée pour quitter...");
    getchar();
    getchar();
    return 0;
}
