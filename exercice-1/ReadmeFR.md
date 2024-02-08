# Exercice 1 : Introduction

Dans cette exercice nous allons introduire les concepts de compilation et des makefiles. Dans le cadre des systèmes embarqués, deux languages sont majoritaires utilisées : le C et le C++. La difference entre ces deux languages reside dans le fait que le C est un language procedurale tandis que le C++ est un language orienté objet. Ces deux languages sont des languages compilés, on utilisera gcc pour le C et g++ pour le C++. Dans ce tutoriel nous nous concentrerons uniquement sur l'utilisation du C. Enfin nous montrerons pourquoi les makefiles sont utiles pour automatiser la compilation de code.

## 1. Introduction à la compilation

Dans cette partie nous allons voir comment fonctionne le compilateur gcc. 
La compilation se fait en 4 étapes :
1. Le prétraitement (preprocessing) : Durant cette étape le préprocesseur effectue des opérations préliminaires sur le code source. Cela inclut l'expansion des directives du préprocesseur (comme les #include en C/C++ qui insèrent le contenu d'autres fichiers, ou les #define qui définissent des macros).
2. La compilation (compilation) : Durant cette étape, le compilateur traduit le code source dans un langage de bas niveau (par exemple, le langage assembleur). 
3. L'assemblage (assembly) : Durant cette étape, le compulateur transforme le code intermédiaire généré à l'étape précédente en code machine spécifique à l'architecture cible. Le résultat est un ensemble de fichiers objet contenant le code machine (en binaire).
4. L'édition de liens (linking) : Lors de cette dernière étape, l'éditeur de liens combine tous les fichiers objet (y compris les bibliothèques nécessaires) en un fichier exécutable unique. Cela inclut la résolution des références aux fonctions et aux variables entre les fichiers.

Effectuons l'ensemble de ces étapes sur le fichier main.c à la racine du dossier (on ignore les dossiers src et inc pour l'instant ):
1. Pour effectuer l'étape de prétraitement il faut executer la commande `gcc -E main.c -o main.i`
2. Pour effectuer l'étape de compilation il faut executer la commande `gcc -S main.i -o main.s`
3. Pour effectuer l'étape d'assemblage il faut executer la commande `gcc -c main.s -o main.o`
4. Pour effectuer l'étape d'édition des liens il faut executer la commande `gcc main.o -o main`

**Remarque :** l'argument "-o filename" indique à gcc sa sortie, "-E" indique que l'on souhaite s'arreter au prétraitement, "-S" indique que l'on souhaite s'arreter à la compilation, "-c" indique que l'on souhaite s'arreter à l'assemblage, pas d'argument indique que l'on souhaite faire la compilation en entier.

**Question 1 :** Executez les 4 commandes `gcc -E main.c -o main.i`, `gcc -S main.i -o main.s`, `gcc -c main.s -o main.o`, `gcc main.o -o main`. Puis executer le programme main en faisant `./main`. Qu'obtenez vous ?

**Question 2 :** Quel est la difference entre le fichier main.c et main.i. A quoi correspondent ces differences ? Le commentaire "// Dumb Comment" ligne 5 est-il toujours présent ?

**Question 3 :** Ouvrir le fichier main.s, quel est son contenu ? Quels sont les labels presents ("toto :" indique le label toto dans le code assembleur).

**Question 4 :** Observons le contenu du fichier .o. Si l'on fait `cat main.o` (cat sert à afficher le contenu d'un fichier texte sur le terminal), qu'observe-t-on ? Est-ce normal ?

**Question 5 :** Utilisons desormais la commande `hexdump -C main.o` pour afficher le contenu du fichier main.o (l'argument -C permet d'afficher l'ASCII équivalent de l'hexa sur une deuxième colonne). Est-ce que l'on retrouve les labels de la questions 3 dans ce dump ?

On peut utiliser la commande objdump pour lire le contenu des fichiers objets.

**Question 6 :** La commande `objdump -t main.o` permet d'afficher les symboles. Les symboles d'un fichier objet regroupes : les sections, les fonctions, les variables gloables et les labels de l'assembleur. Est-ce que l'en faisant `objdump -t main.o` on retrouve les labels de la question 3.

**Question 7 :** La commande `objdump -d main.o` permet de dessasembler le code et de revenir à l'assembleur. Comparer la sortie de la commande `objdump -d main.o` au fichier main.s. Est-ce que les directives assembleurs (les lignes du fichier assembleur qui commence par un . comme ".toto") sont toujours presente ? Est-ce que l'assembleur est pareil au niveau de l'instruction "leaq" (load equivalent address quadword).

Interessons nous au fichier executable main :

**Question 8 :** Si l'on fait `objdump -d main` et que l'on regarde l'instruction "leaq", est-ce que l'on a le même resultat que dans l'assembleur et le fichier objet ? 

L'instruction leaq 21(%rip), %rdi (et son commentaire "## 0x100003f85 <_printf+0x100003f85>") charge dans printf le contenu de l'adresse 0x100003f85. 

**Question 9 :** En faisant un `hexdump -C main` que retrouve-t-on à l'adresse 0x000003f85 ? Remarque : on a ignoré l'offset de 0x100000000 car le hexdump n'affiche pas les addresses tel que le programme sera chargé lors de son execution.

## 2. Introduction aux makefiles

