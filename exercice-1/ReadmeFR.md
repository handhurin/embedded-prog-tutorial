# Exercice 1 : Introduction

Dans cette exercice nous allons introduire les concepts de compilation et des makefiles. Dans le cadre des systèmes embarqués, deux langages sont majoritaires utilisées : le C et le C++. La différence entre ces deux langages réside dans le fait que le C est un language procédurale tandis que le C++ est un language orienté objet. Ces deux langages sont des langages compilés, on utilisera gcc pour le C et g++ pour le C++. Dans ce tutoriel nous nous concentrerons uniquement sur l'utilisation du C. Enfin nous montrerons pourquoi les makefiles sont utiles pour automatiser la compilation de code.

## 1. Introduction à la compilation

Dans cette partie nous allons voir comment fonctionne le compilateur gcc. 
La compilation se fait en 4 étapes :
1. Le prétraitement (preprocessing) : Durant cette étape le préprocesseur effectue des opérations préliminaires sur le code source. Cela inclut l'expansion des directives du préprocesseur (comme les #include en C/C++ qui insèrent le contenu d'autres fichiers, ou les #define qui définissent des macros).
2. La compilation (compilation) : Durant cette étape, le compilateur traduit le code source dans un langage de bas niveau (par exemple, le langage assembleur). 
3. L'assemblage (assembly) : Durant cette étape, le compilateur transforme le code intermédiaire généré à l'étape précédente en code machine spécifique à l'architecture cible. Le résultat est un ensemble de fichiers objet contenant le code machine (en binaire).
4. L'édition de liens (linking) : Lors de cette dernière étape, l'éditeur de liens combine tous les fichiers objet (y compris les bibliothèques nécessaires) en un fichier exécutable unique. Cela inclut la résolution des références aux fonctions et aux variables entre les fichiers.

Effectuons l'ensemble de ces étapes sur le fichier main.c à la racine du dossier (on ignore les dossiers src et inc pour l'instant ):
1. Pour effectuer l'étape de prétraitement il faut exécuter la commande `gcc -E main.c -o main.i`
2. Pour effectuer l'étape de compilation il faut exécuter la commande `gcc -S main.i -o main.s`
3. Pour effectuer l'étape d'assemblage il faut exécuter la commande `gcc -c main.s -o main.o`
4. Pour effectuer l'étape d'édition des liens il faut exécuter la commande `gcc main.o -o main`

**Remarque :** l'argument "-o filename" indique à gcc sa sortie, "-E" indique que l'on souhaite s'arrêter au prétraitement, "-S" indique que l'on souhaite s’arrêter à la compilation, "-c" indique que l'on souhaite s'arrêter à l'assemblage, pas d'argument indique que l'on souhaite faire la compilation en entier.

**Question 1 :** Exécutez les 4 commandes `gcc -E main.c -o main.i`, `gcc -S main.i -o main.s`, `gcc -c main.s -o main.o`, `gcc main.o -o main`. Puis exécuter le programme main en faisant `./main`. Qu'obtenez vous ?

**Question 2 :** Quel est la différence entre le fichier main.c et main.i. A quoi correspondent ces differences ? Le commentaire "// Dumb Comment" ligne 5 est-il toujours présent ?

**Question 3 :** Ouvrir le fichier main.s, quel est son contenu ? Quels sont les labels présents ("toto :" indique le label toto dans le code assembleur).

**Question 4 :** Observons le contenu du fichier .o. Si l'on fait `cat main.o` (cat sert à afficher le contenu d'un fichier texte sur le terminal), qu'observe-t-on ? Est-ce normal ?

**Question 5 :** Utilisons désormais la commande `hexdump -C main.o` pour afficher le contenu du fichier main.o (l'argument -C permet d'afficher l'ASCII équivalent de l'hexadécimale sur une deuxième colonne). Est-ce que l'on retrouve les labels de la questions 3 dans ce dump ? Qu'est devenu le label L_.str ?

On peut utiliser la commande objdump pour lire le contenu des fichiers objets.

**Question 6 :** La commande `objdump -t main.o` permet d'afficher les symboles. Les symboles d'un fichier objet regroupes : les sections, les fonctions, les variables globales et les labels de l'assembleur. Est-ce que l'en faisant `objdump -t main.o` on retrouve le label _main de la question 3.

**Question 7 :** La commande `objdump -d main.o` permet de désassembler le code et de revenir à l'assembleur. Comparer la sortie de la commande `objdump -d main.o` au fichier main.s. Est-ce que les directives assembleurs (les lignes du fichier assembleur qui commence par un . comme ".toto") sont toujours présente ? Est-ce que l'assembleur est pareil au niveau de l'instruction "leaq" (load équivalent address quadword).

Intéressons nous au fichier exécutable main :

**Question 8 :** Si l'on fait `objdump -d main` et que l'on regarde l'instruction "leaq", est-ce que l'on a le même résultat que dans l'assembleur et le fichier objet ? 

L'instruction leaq 21(%rip), %rdi (et son commentaire "## 0x100003f85 <_printf+0x100003f85>") charge dans printf le contenu de l'adresse 0x100003f85. 

**Question 9 :** En faisant un `hexdump -C main` que retrouve-t-on à l'adresse 0x000003f85 ? Remarque : on a ignoré l'offset de 0x100000000 car le hexdump n'affiche pas les addresses tel que le programme sera chargé lors de son execution.

## 2. Introduction aux makefiles

Dans cette deuxième partie nous allons voir l'intérêt des Makefiles pour compiler un projet. Dans un vrai projet, il est rare d'avoir un unique fichier source, on se retrouve le plus souvent avec :
- Une arborescence avec plusieurs dossiers contenant tout les fichiers sources
- Des fichiers sources
- Des fichiers headers

Proposons le petit projet suivant :
- Un dossier src contenant main.c et operations.c
- Un dossier inc contenant header.h et operation.h
- Un dossier build qui contiendra les fichiers compilés

Si l'on souhaite compiler ce projet il faut :
1. Compiler le fichier main.c en main.o
2. Compiler le fichier operations.c en operations.o
3. Linker les deux fichiers ensemble et produire l'exécutable projet

Or pour compiler main.c et operations.c, on doit également inclure les fichiers headers. Pour cela, il faut ajouter lors de la compilation "-I {chemindudossierdesincludes}".
Pour compiler ce projet il faut donc faire :
1. `gcc -c src/main.c -Iinc -o build/main.o`
2. `gcc -c src/operations.c -Iinc -o build/operation.o`
3. `gcc build/main.o build/operation.o -o build/program`
On peut alors exécuter le programme en faisant `./build/program`. 

On comprend vite que compiler un programme avec plusieurs dizaines voir centaine de fichier devient vite un enfer. C'est pourquoi l'outil make a été inventé pour automatiser la compilation.

Nous allons voir comment créer un fichier Makefile pour compiler le projet. Un makefile est basé sur ce qu'on appelle des "cibles" ou "targets" en anglais. La syntaxe est la suivante : 
```
cible : composantes
    commandes
```
Chaque cible est définie par des composantes et des commandes (Remarques : une cible peut avoir 0 composante et 0 commande même si cela ne serait pas très utile).
- Une composante (component en anglais) est une dépendance de la cible, cela peut être un fichier ou une autre cible. Pour que la cible soit réalisée, il faut que 
    - Le fichier existe si la composante est un fichier
    - La cible ai été exécuté.
- Une commande est comme son nom l'indique une commande a exécuter si toutes les composantes sont présentes ou on été exécutées. 

**Question 10 :** Remplir le Makefile avec les cibles suivantes. Quel commande echo sera exécutée en premier et pourquoi ? Exécuter la commande `make` et confirmer (ou infirmer) votre théorie.
```
test1 : test2
	@echo "Echo from test 1"

test2 :
	@echo "Echo from test 2"
```

**Remarque :** Le @ devant echo permet de rendre muet l'appel de la commande. Seul la sortie de la commande apparaît. Si le @ n'était pas présent alors le terminal afficherait 
```
> echo "Echo from test 2"
> Echo from test 2
```

En réalité quand l'on execute la commande `make`, l'outil makefile va automatiquement exécuter la première cible du fichier Makefile (ou du fichier makefile) présent dans le répertoire. Mais l'on peut exécuter une autre cible que la première du fichier. Il suffit de faire `make nomcible`.

**Question 11 :** Exécuter la commande `make test2`, quelle cible est appelée ? Est-ce que test1 est appelé ? Pourquoi ?

Si l'on souhaite exécuter un Makefile qui ne s'appelle pas Makefile ou makefile il faut alors exécuter `make -f nomdufichier`. Mais il est de convention de nommé le Makefile principale Makefile (sans extension).

Un Makefile peut inclure d'autre Makefiles, c'est une méthode souvent utilisé pour ne pas se retrouver avec un Makefile gigantesque mais plusieurs makefile chacun spécialisé pour une action. Il est communément admis que ces makefiles secondaire ont l'extension .mk à la fin du nom du fichier. Pour inclure un makefile dans un makefile il suffit d'écrire `include nomdumakefile`.

Un cas d'utilisation courant des fichiers makefiles secondaires est le fichier path.mk dans lequel on stocke tous les chemins du projet dans des variables.

Pour creer une variable dans un makefile il suffit d'écrire :
``` NOMVARIABLE = valeurvariable ```
Pour utiliser cette variable dans le makefile il suffit de faire 
``` $(NOMVARIABLE) ```

Le fichier paths.mk a été préparé avec les variables WORKSPACE_DIR, SRC_DIR, INC_DIR et BUILD_DIR.

**Question 12 :** Modifier le fichier Makefile précédemment écrit de façon que test1 print le chemin du dossier build et test2 print le chemin des sources et des includes.
La sortie devra être 
```
> Chemin des sources : ./src
> Chemin des includes : ./inc
> Chemin de build : ./build
```

**Question 13 :** Supprimer les cibles test1 et test2 et remplacer les par 3 cibles \$(BUILD_DIR)/program, \$(BUILD_DIR)/main.o, \$(BUILD_DIR)/operations.o. Pour chaque cible indiquer les bonnes composantes et les commandes.

**Question 14 :** Rajouter deux cibles build et clean. La cible build doit être la première cible du fichier makefile et a pour composante \$(BUILD_DIR)/program et pas de commande. Tandis que clean n'a pas de composante et a pour commande `rm -rf build/*`

On peut désormais faire `make clean build`. On peut même créer une cible all qui a pour composante clean et build.

A partit d'ici on devrait se retrouver avec le Makefile suivant :
```
include path.mk

all : clean build

build : $(BUILD_DIR)/program

$(BUILD_DIR)/program : #Mettre les dependances
	#Mettre la commande

$(BUILD_DIR)/main.o : #Mettre les dependances
	#Mettre la commande

$(BUILD_DIR)/operations.o : #Mettre les dependances
	#Mettre la commande

clean :
	rm -rf build/*
```

Plutôt que d'avoir à recopier dans la commande la cible et les dépendances on peut utiliser "\$^" au lieu des composantes et "\$@" au lieu de la cible. Par exemple 

```
toto.o : toto.c
    gcc -c toto.c -o toto.o
```
Devient :
```
toto.o : toto.c
    gcc -c $^ -o $@
```

**Question 15 :** Modifier le makefile de façon à que les commandes n'utilisent plus que \$^ et \$@.

On remarque alors que les cibles main.o et operations.o ont exactement la même commande `gcc -c $^ -I$(INC_DIR) -o $@`. On pourrait donc utilise un moyen de créer une cible générique pour tous les fichiers objets. Pour cela utilisons l'opérateur % qui équivaut à "pour tout élément".
Par exemple :
```
$(PDF_DIR)/%.pdf : $(TXT_DIR)/%.txt
    #Commande de conversion txt en pdf
```
Est une cible générique pour générer un pdf basé sur un fichier text.

**Question 16 :** Remplacer les cibles \$(BUILD_DIR)/main.o et \$(BUILD_DIR)/operations.o par une seule cible en utilisant %.

On doit alors se retrouver avec le makefile suivant :
```
include path.mk

all : clean build

build : $(BUILD_DIR)/program

$(BUILD_DIR)/program : #liste des fichiers .o
	gcc $^ -o $@

# cible_o_generique : composante_c_generique
    gcc -c $^ -I$(INC_DIR) -o $@

clean :
	rm -rf build/*
```

Il reste un dernier problème qu'on aimerai résoudre : pour la cible programme on se retrouve a devoir lister tous les fichiers objets dans les composantes. On aimerait bien avoir une variable qui contient automatiquement les fichiers objets.
On propose alors de créer une variable SRCS contenant tous les fichiers sources et OBJS contenant tous les fichiers OBJS.

**Question 17 :** Créer la variable SRCS en listant dedans tous les fichiers sources. Puis créer la variable OBJS en faisant `OBJS = $(SRCS:.c=.o)` (Cela signifie qu'on prend tous les éléments de SRCS et qu'on modifie l'extension .c en .o). Modifier le makefile en conséquence.

Pour l'instant nous n'avons fait que décaler le problème : au lieu d'avoir la liste des fichiers objets dans la cible \$(BUILD_DIR)/program on l'a dans la variable SRCS. On peut alors utiliser la commande `wildcard *` qui répertorie tous les éléments du répertoire présent. Pour que SRCS contient tous les fichiers sources du dossier src il suffit de faire `SRCS = $(wildcard $(SRC_DIR)/*.c)`

**Question 18 :** Modifier le makefile en conséquence.

On peut même créer une variable TARGET qui contient la cible (ici \$(BUILD_DIR)/program\) et de remplacer \$(BUILD_DIR)/program par target ce qui sera plus esthétique.

Un beau makefile à la fin de cette exercice doit ressembler au suivant :
```
# Makefile for Exercice 1
include path.mk

TARGET  = $(BUILD_DIR)/program
SRCS 	= $(BUILD_DIR)/main.c $(BUILD_DIR)/operations.c
OBJS    = $(SRCS:.c=.o)

all : clean build

build : $(TARGET)

$(TARGET) : $(OBJS)
	gcc $^ -o $@

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	gcc -c $^ -I$(INC_DIR) -o $@

clean :
	rm -rf build/*
```
