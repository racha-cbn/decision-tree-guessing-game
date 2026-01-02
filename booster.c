#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET "\033[0m"
#define ROUGE "\033[31m"
#define VERT "\033[32m"
#define BLEU "\033[34m"
#define MAGENTA "\033[35m"
#define ORANGE "\033[33m"
#define SIZE 50

/* ===================== STRUCTURE ===================== */
typedef struct noeud {
    char T[SIZE];
    struct noeud* Gnon;
    struct noeud* Doui;
} noeud;

/* ===================== UTILITAIRES ===================== */
void clear_screen() {
    printf("\033[2J\033[H");
}


void afficher_titre(const char* titre) {
    clear_screen();
    printf(BLEU);
    printf("╔════════════════════════════════════╗\n");
    printf("║ %-34s ║\n", titre);
    printf("╚════════════════════════════════════╝\n");
    printf(RESET);
}




void nettoyer(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

char lireChoix() {
    char buf[10];
    fgets(buf, sizeof(buf), stdin);
    return buf[0];
}

int estvide(noeud* root) {
    return (root == NULL);
}

int estfeuille(noeud* root) {
    if (!root) return 0;
    return (root->Gnon == NULL && root->Doui == NULL);
}

int fichier_existe(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f) {
        fclose(f);
        return 1;
    }
    return 0;
}

/* ===================== CREATION ET INSERTION ===================== */
noeud* creerNoeud(const char *str) {
    noeud* n = malloc(sizeof(noeud));
    if (!n) {
        printf("Erreur allocation mémoire !\n");
        exit(1);
    }
    strcpy(n->T, str);
    n->Gnon = NULL;
    n->Doui = NULL;
    return n;
}

noeud* inserer(noeud* parent, const char *str, int cote) {
    noeud* n = creerNoeud(str);
    if (cote)
        parent->Doui = n;
    else
        parent->Gnon = n;
    return n;
}

/* ===================== APPRENTISSAGE ===================== */
void apprendre(noeud* feuille) {
    char ancien[SIZE], nouveau[SIZE], question[SIZE];
    char rep;

    strcpy(ancien, feuille->T);

    printf(ROUGE "J'ai perdu 😅 Quel était l'animal/objet/métier ? : " RESET);
    fgets(nouveau, SIZE, stdin);
    nettoyer(nouveau);

    printf("Quelle question différencie un %s d'un %s ? : ", ancien, nouveau);
    fgets(question, SIZE, stdin);
    nettoyer(question);

    do {
        printf("Pour un %s, la réponse est Oui ou Non ? (o/n) : ", nouveau);
        rep = lireChoix();
    } while (rep != 'o' && rep != 'O' && rep != 'n' && rep != 'N');

    noeud* ancienG = feuille->Gnon;
    noeud* ancienD = feuille->Doui;

    strcpy(feuille->T, question);

    if (rep == 'o' || rep == 'O') {
        feuille->Doui = creerNoeud(nouveau);   // Oui → nouveau
        feuille->Gnon = creerNoeud(ancien);    // Non → ancien
        feuille->Gnon->Gnon = ancienG;
        feuille->Gnon->Doui = ancienD;
    } else {
        feuille->Gnon = creerNoeud(nouveau);   // Non → nouveau
        feuille->Doui = creerNoeud(ancien);    // Oui → ancien
        feuille->Doui->Gnon = ancienG;
        feuille->Doui->Doui = ancienD;
    }
}

/* ===================== AFFICHAGE ===================== */
void afficherArbre(noeud* root, char* prefix, int isLeft) {
    if (!root) return;

    printf("%s", prefix);
    printf(isLeft ? "|-- " : "\\-- ");

    if (estfeuille(root))
        printf(VERT "%s\n" RESET, root->T);
    else
        printf(BLEU "%s\n" RESET, root->T);

    char newPrefix[200] = "";
    strcpy(newPrefix, prefix);
    strcat(newPrefix, isLeft ? "|   " : "    ");

    if (root->Doui) afficherArbre(root->Doui, newPrefix, 1);
    if (root->Gnon) afficherArbre(root->Gnon, newPrefix, 0);
}

/* ===================== SAUVEGARDE ===================== */
void sauvegarderArbreStruct(noeud* root, FILE* f) {
    if (!root) {
        fprintf(f, "#\n");
        return;
    }
    if (estfeuille(root))
        fprintf(f, "A|%s\n", root->T);
    else
        fprintf(f, "Q|%s\n", root->T);

    sauvegarderArbreStruct(root->Gnon, f);  // Non d'abord
    sauvegarderArbreStruct(root->Doui, f);  // Oui ensuite
}

void enregistrerArbreParCategorie(noeud* root, const char* categorie) {
    char filename[50];
    sprintf(filename, "%s.txt", categorie);
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Erreur: impossible de créer le fichier %s.\n", filename);
        return;
    }
    sauvegarderArbreStruct(root, f);
    fclose(f);
    printf("Arbre sauvegardé dans '%s'\n", filename);
}

/* ===================== CHARGEMENT ===================== */
noeud* chargerArbreStruct(FILE* f) {
    char ligne[SIZE + 10];
    if (!fgets(ligne, sizeof(ligne), f)) return NULL;
    nettoyer(ligne);
    if (strcmp(ligne, "#") == 0) return NULL;

    // ligne commence par 'Q' ou 'A'
    noeud* n = creerNoeud(ligne + 2); // saute "A|" ou "Q|"

    n->Gnon = chargerArbreStruct(f);  // Non d'abord
    n->Doui = chargerArbreStruct(f);  // Oui ensuite

    return n;
}


noeud* chargerArbreParCategorie(const char* categorie) {
    char filename[50];
    sprintf(filename, "%s.txt", categorie);
    if (!fichier_existe(filename)) return NULL;

    FILE* f = fopen(filename, "r");
    if (!f) return NULL;

    noeud* root = chargerArbreStruct(f);
    fclose(f);
    return root;
}

/* ===================== SUPPRIMER SAUVGARDE ===================== */
void supprimerArbreSauvegarde(const char* categorie) {
    char filename[50];
    sprintf(filename, "%s.txt", categorie);
    if (remove(filename) == 0) {
        printf("La sauvegarde '%s' a été supprimée.\n", filename);
    } else {
        printf("Impossible de supprimer '%s' (fichier peut ne pas exister).\n", filename);
    }
}

/* ===================== JEU ===================== */
void question(noeud* root) {
    if (!root) return;

    noeud* courant = root;

    while (!estfeuille(courant)) {
        char rep;
        noeud* suivant;

        printf(BLEU "%s (o/n) : " RESET, courant->T);
        rep = lireChoix();

        if (rep == 'o' || rep == 'O')
            suivant = courant->Doui;
        else if (rep == 'n' || rep == 'N')
            suivant = courant->Gnon;
        else {
            printf("Réponse invalide.\n");
            return;
        }

        if (!suivant) {
            // Cas improbable dans un arbre bien formé, on arrête proprement
            return;
        }

        courant = suivant;
    }

    // On est arrivé à une feuille
    char rep;
    printf("\nEst-ce un %s ? (o/n) : ", courant->T);
    rep = lireChoix();

    if (rep == 'o' || rep == 'O') {
        printf(MAGENTA "\nBien joué ! 🎉\n" RESET);
    } else if (rep == 'n' || rep == 'N') {
        apprendre(courant);
        printf("\nArbre mis à jour !\n");
    } else {
        printf("Réponse invalide.\n");
    }
}

/* ===================== STATISTIQUES ===================== */
int hauteur(noeud* root) {
    if (!root) return 0;
    int g = hauteur(root->Gnon);
    int d = hauteur(root->Doui);
    return 1 + (g > d ? g : d);
}

int nbNoeuds(noeud* root) {
    if (!root) return 0;
    return 1 + nbNoeuds(root->Gnon) + nbNoeuds(root->Doui);
}

int nbFeuilles(noeud* root) {
    if (!root) return 0;
    if (estfeuille(root)) return 1;
    return nbFeuilles(root->Gnon) + nbFeuilles(root->Doui);
}

void sommeProfondeur(noeud* root, int prof, int* sum, int* count) {
    if (!root) return;
    if (estfeuille(root)) {
        *sum += prof;
        (*count)++;
        return;
    }
    sommeProfondeur(root->Gnon, prof + 1, sum, count);
    sommeProfondeur(root->Doui, prof + 1, sum, count);
}

double profondeurMoyenne(noeud* n) {
    int sum = 0, count = 0;
    if (estvide(n)) return 0.0;
    sommeProfondeur(n, 1, &sum, &count);
    return count == 0 ? 0.0 : (double)sum / count;
}

void montrer_statistiques(noeud* root) {
    printf(ORANGE "\n===== STATISTIQUES =====\n" RESET);
    printf(ORANGE "Hauteur : %d\n" RESET, hauteur(root));
    printf(ORANGE "Nombre de nœuds : %d\n" RESET, nbNoeuds(root));
    printf(ORANGE "Nombre de feuilles : %d\n" RESET, nbFeuilles(root));
    printf(ORANGE "Profondeur moyenne des feuilles : %.2f\n" RESET, profondeurMoyenne(root));
}

/* ===================== LIBERATION MEMOIRE ===================== */
void libererArbre(noeud* root) {
    if (!root) return;
    libererArbre(root->Gnon);
    libererArbre(root->Doui);
    free(root);
}

/* ===================== INITIALISATION ===================== */
void animal(noeud** root) {
    *root = chargerArbreParCategorie("animaux");
    if (*root) {
        printf("Arbre 'Animaux' chargé depuis le fichier.\n");
        return;
    }
    *root = creerNoeud("Est-ce un mammifère ?");
    noeud* non = inserer(*root, "Est-ce un reptile ?", 0);
    noeud* oui = inserer(*root, "Est-ce un animal domestique ?", 1);
    inserer(non, "Serpent", 1);
    inserer(non, "Aigle", 0);
    inserer(oui, "Chat", 1);
    inserer(oui, "Dauphin", 0);
}

void metier(noeud** root) {
    *root = chargerArbreParCategorie("metiers");
    if (*root) {
        printf("Arbre 'Métiers' chargé depuis le fichier.\n");
        return;
    }
    *root = creerNoeud("Travaille-t-il dans un bureau ?");
    noeud* oui = inserer(*root, "Utilise-t-il beaucoup un ordinateur ?", 1);
    noeud* non = inserer(*root, "Est-ce un métier manuel ?", 0);
    inserer(oui, "Ingénieur", 1);
    inserer(oui, "Secrétaire", 0);
    inserer(non, "Policier", 1);
    inserer(non, "Cuisinier", 0);
}

void objet(noeud** root) {
    *root = chargerArbreParCategorie("objets");
    if (*root) {
        printf("Arbre 'Objets' chargé depuis le fichier.\n");
        return;
    }
    *root = creerNoeud("Est-ce un objet électronique ?");
    noeud* oui = inserer(*root, "Est-ce portable ?", 1);
    noeud* non = inserer(*root, "Est-ce du mobilier ?", 0);
    inserer(oui, "Téléphone", 1);
    inserer(oui, "Télévision", 0);
    inserer(non, "Chaise", 1);
    inserer(non, "Livre", 0);
}

/* ===================== MENU ===================== */
void categorie(noeud** root, const char** categorieNom) {
    int choix;
    char buf[10];

    printf("\n=== Choix de la catégorie ===\n");
    printf("1. Animaux\n2. Métiers\n3. Objets\nVotre choix : ");
    fgets(buf, sizeof(buf), stdin);
    choix = atoi(buf);

    switch (choix) {
        case 1:
            printf("\nCatégorie choisie : Animaux 🐾\n");
            animal(root);
            *categorieNom = "animaux";
            break;
        case 2:
            printf("\nCatégorie choisie : Métiers 🧑‍💼\n");
            metier(root);
            *categorieNom = "metiers";
            break;
        case 3:
            printf("\nCatégorie choisie : Objets 📦\n");
            objet(root);
            *categorieNom = "objets";
            break;
        default:
            printf("\nChoix invalide.\n");
            *root = NULL;
            *categorieNom = NULL;
    }
}



void menu_principal(noeud* root, const char* categorieNom) {
    int choix;
    char buf[10];

    do {
        afficher_titre("MENU PRINCIPAL");

        printf(VERT " Catégorie : %s\n\n" RESET,
               categorieNom ? categorieNom : "Aucune");

        printf("  " ORANGE "▶ 1" RESET "  Jouer\n");
        printf("  " ORANGE "▶ 2" RESET "  Statistiques\n");
        printf("  " ORANGE "▶ 3" RESET "  Afficher l'arbre\n");
        printf("  " ORANGE "▶ 4" RESET "  Sauvegarder\n");
        printf("  " ORANGE "▶ 5" RESET "  Supprimer sauvegarde\n");
        printf("  " ORANGE "▶ 6" RESET "  Quitter\n");

        printf("\n" BLEU " Choix > " RESET);
        fgets(buf, sizeof(buf), stdin);
        choix = atoi(buf);

        switch (choix) {
            case 1: question(root); break;
            case 2: montrer_statistiques(root); break;
            case 3: afficherArbre(root, "", 0); break;
            case 4:
                if (categorieNom) enregistrerArbreParCategorie(root, categorieNom);
                break;
            case 5:
                if (categorieNom) supprimerArbreSauvegarde(categorieNom);
                break;
            case 6: break;
            default:
                printf(ROUGE "\n Choix invalide\n" RESET);
        }

        if (choix != 6) {
            printf("\nAppuyez sur Entrée pour continuer...");
            getchar();
        }

    } while (choix != 6);
}




void menu(noeud** root) {
    const char* categorieNom = NULL;
    categorie(root, &categorieNom);

    if (*root == NULL) {
        printf("Aucune catégorie valide sélectionnée. Fin du programme.\n");
        return;
    }

    menu_principal(*root, categorieNom);
}


/* ===================== MAIN ===================== */
int main() {
    noeud* root = NULL;
    menu(&root);
    libererArbre(root);
    return 0;
}