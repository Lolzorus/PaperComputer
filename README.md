# Paper computer / Ordinateur en Papier
This project implements a simulated paper computer in C, capable of executing simple programs defined in a text file.
It uses limited memory (256 locations) and a basic set of commands for performing calculations and I/O operations.
This program is designed for first-year students.

# Features
# Simulation of a Basic Computer:
Memory of 256 slots.
Main registers: RS, RM, PC, RI, A.

# Program Loading:
Programs defined in a text file in hexadecimal format.

# Instruction Set:
Arithmetic instructions (ADD, SUB).
Loading and storing values (LOAD, STORE).
Input and output operations (IN, OUT).
Flow control (JUMP, BRZ, BRN).
Program Termination:
Stops when a 0xFF instruction is encountered or if an error occurs.
Program Structure
The code is divided into several main functions:

# Initialization
flush_memoire: Initializes memory to 0.
charger_programme: Loads a program from an in-memory structure.
charger_programme_depuis_fichier: Reads a program from a text file.
Execution
recuperer_instruction: Fetches the instruction at the current program counter (PC) address.
executer_instruction: Executes an instruction based on its opcode.
executer: Main loop that runs the program until termination.
Program File Format
Each line in the file must contain two hexadecimal values separated by a space:

Opcode: Specifies the operation to perform.
Operand: Parameter for the operation (can be an immediate value or a memory address).

#  Example Program File:
00 05   # LOAD #5
20 03   # ADD #3
41 00   # OUT a
FF 00   # Terminate

# Available Instructions
Opcode   Instruction   Description
0x00   LOAD #v   Loads an immediate value.
0x40   LOAD a   Loads a value at a relative address.
0xC0   LOAD *a   Loads a value at an indirect address.
0x20   ADD #v   Adds an immediate value.
0x60   ADD a   Adds a value from a memory address.
0xE0   ADD *a   Adds a value from an indirect address.
0x21   SUB #v   Subtracts an immediate value.
0x61   SUB a   Subtracts a value from memory.
0xE1   SUB *a   Subtracts a value from an indirect address.
0x48   STORE a   Stores the accumulator in memory.
0x49   IN a   Reads input and stores it.
0xC9   IN *a   Reads input and stores it indirectly.
0x41   OUT a   Outputs a value from a memory address.
0xC1   OUT *a   Outputs a value indirectly.
0x10   JUMP a   Unconditional jump.
0x12   BRZ a   Jump if the accumulator is zero.
0x11   BRN a   Jump if the accumulator is negative.
0xFF   -   Stops the program.

# Compilation and Execution
# Compile the Program:
Use a standard gcc command:
gcc -o ordinateur paper_computer.c

#  Run with a Program File:
./ordinateur program_file.txt

# Example Program File (program_file.txt):
00 10   # LOAD #16
20 10   # ADD #16
41 00   # OUT a
FF 00   # Terminate

# Expected Output:
Output: 32

# Limitations
Memory is limited to 256 slots.
Values are treated as integers.
Jumps outside the memory range halt the execution.

# Possible Improvements
Add an interactive debugger.
Extend the instruction set.
Implement more robust error handling.

# Author
This project was designed as a simulation of a basic computer to help learn the principles of computer architecture and machine instruction execution in a first-year imperative programming course.


## Francais
Ce projet implémente un ordinateur en papier simulé en C, capable d'exécuter des programmes simples définis dans un fichier texte. 
Il utilise une mémoire limitée (256 emplacements) et un ensemble de commandes basiques pour effectuer des calculs et des opérations d'E/S.
Il s'agit d'un programme de premiere annee.

# Fonctionnalités

# Simulation d'un ordinateur basique :
Mémoire de 256 cases.
Registres principaux : RS, RM, PC, RI, A.
Chargement de programmes :
Programmes définis dans un fichier texte au format hexadécimal.
Ensemble d'instructions :
Instructions arithmétiques (ADD, SUB).
Chargement et stockage de valeurs (LOAD, STORE).
Entrées et sorties (IN, OUT).
Contrôle de flux (JUMP, BRZ, BRN).
Arrêt du programme lorsqu'une instruction 0xFF est rencontrée ou si une erreur se produit.
Structure du programme


# Le code se décompose en plusieurs fonctions principales :
# Initialisation
flush_memoire : Initialise la mémoire à 0.
charger_programme : Charge un programme depuis une structure en mémoire.
charger_programme_depuis_fichier : Lit un programme depuis un fichier texte.
Exécution
recuperer_instruction : Récupère l'instruction à l'adresse courante du compteur de programme (PC).
executer_instruction : Exécute une instruction en fonction de l'opcode.
executer : Boucle principale exécutant le programme jusqu'à l'arrêt.
Format du fichier programme
Chaque ligne du fichier doit contenir deux valeurs hexadécimales séparées par un espace :

Opcode : Spécifie l'opération à effectuer.
Opérande : Paramètre de l'opération (peut être une valeur immédiate ou une adresse mémoire).

# Exemple de fichier programme :
00 05   # LOAD #5
20 03   # ADD #3
41 00   # OUT a
FF 00   # Arrêt

# Instructions disponibles

# Opcode   Instruction   Description
0x00   LOAD #v   Charge une valeur immédiate.
0x40   LOAD a   Charge une valeur à une adresse relative.
0xC0   LOAD *a   Charge une valeur à une adresse indirecte.
0x20   ADD #v   Ajoute une valeur immédiate.
0x60   ADD a   Ajoute une valeur depuis une adresse mémoire.
0xE0   ADD *a   Ajoute une valeur depuis une adresse indirecte.
0x21   SUB #v   Soustrait une valeur immédiate.
0x61   SUB a   Soustrait une valeur depuis une adresse mémoire.
0xE1   SUB *a   Soustrait une valeur depuis une adresse indirecte.
0x48   STORE a   Stocke l'accumulateur dans une adresse mémoire.
0x49   IN a   Lit une entrée et la stocke.
0xC9   IN *a   Lit une entrée et la stocke indirectement.
0x41   OUT a   Affiche une valeur à une adresse mémoire.
0xC1   OUT *a   Affiche une valeur indirectement.
0x10   JUMP a   Saut inconditionnel.
0x12   BRZ a   Saut si l'accumulateur est 0.
0x11   BRN a   Saut si l'accumulateur est négatif.
0xFF   -   Arrête le programme.

# Compilation et exécution
# Compiler le programme avec une commande gcc standard (ex gcc -o ordinateur papier_ordinateur.c)

# Exécuter avec un fichier programme :
./ordinateur nom_du_fichier.txt

# Exemple de fichier programme.txt :
00 10   # LOAD #16
20 10   # ADD #16
41 00   # OUT a
FF 00   # Arrêt

# Résultat attendu :
Output: 32


# Limitations
La mémoire est limitée à 256 cases.
Les valeurs sont manipulées comme des entiers.
Les sauts hors de la plage mémoire arrêtent l'exécution.

# Améliorations possibles
Ajouter un débogueur interactif.
Étendre l'ensemble d'instructions.
Implémenter une gestion plus robuste des erreurs.

# Auteur
Ce projet a été conçu comme une simulation d'un ordinateur basique pour apprendre les principes de l'architecture des ordinateurs et l'exécution des instructions machine lors du cours de programmation imperative de premiere annee
