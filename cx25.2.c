#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MEMORY_SIZE 256

// Structure de base de l'ordinateur en papier
typedef struct {
    int memoire[MEMORY_SIZE];
    int RS;
    int RM;
    int PC;
    int RI[2];
    int A;
} Ordinateur;

void flush_memoire(Ordinateur* ordinateur) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        ordinateur->memoire[i] = 0;
    }
}

void charger_programme(Ordinateur* ordinateur, int programme[][2], int programme_length) {
    int adresse = 0;
    for (int i = 0; i < programme_length; i++) {
        ordinateur->memoire[adresse] = programme[i][0];
        ordinateur->memoire[adresse + 1] = programme[i][1];
        adresse += 2;
    }
}

void charger_programme_depuis_fichier(Ordinateur* ordinateur, const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int programme[MEMORY_SIZE][2];
    int programme_length = 0;

    char ligne[256];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        ligne[strcspn(ligne, "\n")] = '\0';  // retire newline

        if (ligne[0] != '#' && ligne[0] != '\0') {
            int opcode, operande;
            sscanf(ligne, "%x %x", &opcode, &operande);
            programme[programme_length][0] = opcode;
            programme[programme_length][1] = operande;
            programme_length++;
        }
    }

    fclose(fichier);

    charger_programme(ordinateur, programme, programme_length);
}
// Message d'erreur si le programme depasse la plage memoire
void recuperer_instruction(Ordinateur* ordinateur) {
    int pc = ordinateur->PC;
    if (pc >= MEMORY_SIZE) {
        printf("Arrêt du programme.\n");
        ordinateur->RI[0] = 0xFF;  // Arrête le programme
        return;
    }

    ordinateur->RI[0] = ordinateur->memoire[pc];
    ordinateur->RI[1] = (pc + 1 < MEMORY_SIZE) ? ordinateur->memoire[pc + 1] : 0;
}
// Liste d'instruction en utilisant case
void executer_instruction(Ordinateur* ordinateur) {
    recuperer_instruction(ordinateur);
    int opcode = ordinateur->RI[0];
    int operande = ordinateur->RI[1];
    int a = ordinateur->A;
    int rm = ordinateur->RM;

    switch (opcode) {
    case 0x20:  // ADD #v
        ordinateur->A = a + operande;
        break;
    case 0x60:  // ADD a
        ordinateur->A = a + ordinateur->memoire[operande];
        break;
    case 0xE0:  // ADD *a
        {
            int adresse_a = ordinateur->memoire[operande];
            ordinateur->A += ordinateur->memoire[adresse_a];
        }
        break;
    case 0x00:  // LOAD #v
        ordinateur->A = operande;
        break;
    case 0x40:  // LOAD a
        ordinateur->A = ordinateur->memoire[rm + operande];
        break;
    case 0xC0:  // LOAD *a
        {
            int adresse_a = ordinateur->memoire[rm + operande];
            ordinateur->A = ordinateur->memoire[adresse_a];
        }
        break;
    case 0x48:  // STORE a
        ordinateur->memoire[operande] = a;
        break;
    case 0x21:  // SUB #v
        ordinateur->A = a - operande;
        break;
    case 0x61:  // SUB a
        ordinateur->A = a - ordinateur->memoire[operande];
        break;
    case 0xE1:  // SUB *a
        {
            int adresse_a = ordinateur->memoire[operande];
            ordinateur->A -= ordinateur->memoire[adresse_a];
        }
        break;
    case 0x49:  // IN a
        {
            int valeur_entree;
            printf("Input: ");
            scanf("%d", &valeur_entree);
            ordinateur->memoire[rm + operande] = valeur_entree;
        }
        break;
    case 0xC9:  // IN *a
        {
            int adresse_a = ordinateur->memoire[operande];
            int valeur_entree;
            printf("Input: ");
            scanf("%d", &valeur_entree);
            ordinateur->memoire[adresse_a] = valeur_entree;
        }
        break;
    case 0x41:  // OUT a
        printf("Output: %d\n", ordinateur->memoire[rm + operande]);
        break;
    case 0xC1:  // OUT *a
        {
            int adresse_a = ordinateur->memoire[rm + operande];
            printf("Output: %d\n", ordinateur->memoire[adresse_a]);
        }
        break;
    case 0x10:  // JUMP a
        ordinateur->PC = operande;
        break;
    case 0x12:  // BRZ
        if (a == 0) {
            ordinateur->PC = operande;
        }
        break;
    case 0x11:  // BRN
        if (a < 0) {
            ordinateur->PC = operande;
        }
        break;
    default:
        break;
    }
// Saut prochaine instruction
    ordinateur->PC += 2;
}

void executer(Ordinateur* ordinateur) {
    while (1) {
        recuperer_instruction(ordinateur);
        int opcode = ordinateur->RI[0];
        if (opcode == 0xFF) {
            break;
        }
        executer_instruction(ordinateur);
    }
}
// execution du programme sous la forme nom programme nom fichier
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <entrez nom ficher.txt>\n", argv[0]);
        return 1;
    }

    Ordinateur ordinateur;
    flush_memoire(&ordinateur);
    charger_programme_depuis_fichier(&ordinateur, argv[1]);
    executer(&ordinateur);

    return 0;
}
