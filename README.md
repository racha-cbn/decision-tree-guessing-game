# 🌳 Jeu de Devinette par Arbre de Décision / Decision Tree Guessing Game

🇫🇷  
🎯 Objectif  
Concevoir et implémenter un jeu de devinette style **Akinator** en langage C, utilisant un arbre binaire de décision. Le programme pose des questions oui/non pour deviner à quoi l'utilisateur pense, et apprend automatiquement de nouvelles réponses quand il se trompe !

🧠 Description  
Le programme utilise un **arbre binaire de décision** où :  
- Les nœuds internes contiennent des questions (oui/non)  
- Les feuilles contiennent les réponses (animaux, métiers, objets)  

Lorsqu'il perd, le programme demande une nouvelle question et un nouvel élément, puis réorganise l'arbre pour apprendre.  
L'arbre est persistant : il se sauvegarde et se charge depuis des fichiers texte par catégorie.

⚙️ Technologies utilisées  
- Langage : **C** (standard C99/C11)  
- Bibliothèques :  
  `<stdio.h>`, `<stdlib.h>`, `<string.h>`  
- Couleurs terminal ANSI pour une interface agréable

💡 Fonctionnalités principales  
- 3 catégories intégrées : Animaux 🐾, Métiers 🧑‍💼, Objets 📦  
- Apprentissage automatique : l'arbre s'enrichit après chaque défaite  
- Sauvegarde/chargement automatique des arbres (fichiers `animaux.txt`, `metiers.txt`, `objets.txt`)  
- Affichage textuel de l'arbre complet  
- Statistiques détaillées (hauteur, nombre de nœuds/feuilles, profondeur moyenne)  
- Interface colorée avec menus clairs et gestion des entrées utilisateur  
- Suppression de sauvegarde possible

🧩 Exemple d’exécution  
1. Lancement du programme → choix de catégorie  
2. Le jeu pose des questions oui/non  
3. Si bonne réponse → "Bien joué ! 🎉"  
4. Si mauvaise → demande une nouvelle question + nouvel élément → arbre mis à jour et sauvegardé  

📈 Compétences démontrées  
- Structures de données : arbres binaires (pointeurs, récursion)  
- Gestion dynamique de la mémoire (malloc/free)  
- Manipulation de fichiers (lecture/écriture récursive)  
- Algorithmes récursifs (parcours, insertion, statistiques)  
- Interface utilisateur en console (couleurs, menus, robustesse)  
- Programmation modulaire et propre

👨‍💻 Auteur  
Développé par **Chabane Racha Nour** (@racha-cbn)  
Étudiante en 2ᵉ année d'informatique

📁 Fichiers du projet  
- `booster.c`  → code source principal complet  
- `animaux.txt`, `metiers.txt`, `objets.txt` → sauvegardes des arbres (générés automatiquement)  

---

🇬🇧  
🎯 Objective  
Design and implement an **Akinator-style** guessing game in C, using a binary decision tree. The program asks yes/no questions to guess what the user is thinking of, and automatically learns new answers when it fails!

🧠 Description  
The program uses a **binary decision tree** where:  
- Internal nodes contain yes/no questions  
- Leaves contain answers (animals, jobs, objects)  

When it loses, the program asks for a new distinguishing question and a new item, then reorganizes the tree to learn.  
The tree is persistent: saved and loaded from text files per category.

⚙️ Technologies  
- Language: **C** (standard C99/C11)  
- Libraries:  
  `<stdio.h>`, `<stdlib.h>`, `<string.h>`  
- ANSI terminal colors for a nice interface

💡 Main Features  
- 3 built-in categories: Animals 🐾, Jobs 🧑‍💼, Objects 📦  
- Automatic learning: the tree grows after each loss  
- Automatic save/load of trees (files `animaux.txt`, `metiers.txt`, `objets.txt`)  
- Textual display of the full tree  
- Detailed statistics (height, number of nodes/leaves, average depth)  
- Colorful interface with clear menus and input handling  
- Option to delete saves

🧩 Example Workflow  
1. Launch the program → choose a category  
2. The game asks yes/no questions  
3. If correct → "Well played! 🎉"  
4. If wrong → asks for a new question + new item → tree updated and saved  

📈 Skills Demonstrated  
- Data structures: binary trees (pointers, recursion)  
- Dynamic memory management (malloc/free)  
- File handling (recursive read/write)  
- Recursive algorithms (traversal, insertion, statistics)  
- Console user interface (colors, menus, robustness)  
- Clean and modular programming

👨‍💻 Author  
Developed by **Chabane Racha Nour** (@racha-cbn)  
2nd year Computer Science student

📁 Project Files  
- `booster.c`  → main complete source code  
- `animaux.txt`, `metiers.txt`, `objets.txt` → tree saves (auto-generated)  
