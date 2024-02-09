# Exercice 1 : Introduction

Dans cette exercice nous allons introduire les concepts de compilation et des makefiles. Dans le cadre des systèmes embarqués, deux languages sont majoritaires utilisées : le C et le C++. La difference entre ces deux languages reside dans le fait que le C est un language procedurale tandis que le C++ est un language orienté objet. Ces deux languages sont des languages compilés, on utilisera gcc pour le C et g++ pour le C++. Dans ce tutoriel nous nous concentrerons uniquement sur l'utilisation du C. Enfin nous montrerons pourquoi les makefiles sont utiles pour automatiser la compilation de code.

## 1 Introduction to compilation

In this section we will look at how the gcc compiler works. 
Compiling is done in 4 stages:
1. Preprocessing: During this stage, the preprocessor performs preliminary operations on the source code. This includes the expansion of preprocessor directives (such as #include in C/C++, which inserts the contents of other files, or #define, which defines macros).
2. Compilation: During this stage, the compiler translates the source code into a low-level language (for example, assembly language). 
3. Assembly: During this stage, the compiler transforms the intermediate code generated in the previous stage into machine code specific to the target architecture. The result is a set of object files containing the machine code (in binary).
4. Linking: In this final stage, the linker combines all the object files (including the necessary libraries) into a single executable file. This includes resolving references to functions and variables between files.

Let's perform all these steps on the main.c file at the root of the folder (we'll ignore the src and inc folders for now):
1. To perform the pre-processing step, run the command `gcc -E main.c -o main.i`.
2. To compile, run `gcc -S main.i -o main.s`.
3. To perform the assembly step, run the command `gcc -c main.s -o main.o`.
4. To edit the links, run the command `gcc main.o -o main`.

**Note:** the argument "-o filename" indicates to gcc its output, "-E" indicates that you wish to stop at pre-processing, "-S" indicates that you wish to stop at compilation, "-c" indicates that you wish to stop at assembly, no argument indicates that you wish to compile in its entirety.

**Question 1:** Execute the 4 commands `gcc -E main.c -o main.i`, `gcc -S main.i -o main.s`, `gcc -c main.s -o main.o`, `gcc main.o -o main`. Then run the main program as `./main`. What do you get?

**Question 2:** What is the difference between the file main.c and main.i? What do these differences correspond to? Is the comment "// Dumb Comment" on line 5 still present?

**Question 3 :** Open the file main.s, what are its contents? What labels are present ("toto:" indicates the label toto in the assembly code).

**Question 4 :** Let's look at the contents of the .o file. If we run `cat main.o` (cat is used to display the contents of a text file on the terminal), what do we see? Is this normal?

**Question 5:** Now let's use the command `hexdump -C main.o` to display the contents of the file main.o (the -C argument is used to display the ASCII equivalent of the hexa in a second column). Are the labels from question 3 present in this dump? What has happened to the L_.str label?

You can use the objdump command to read the contents of the object files.

**Question 6:** The command `objdump -t main.o` displays the symbols. The symbols in an object file include: sections, functions, global variables and assembler labels. Will `objdump -t main.o` show the _main label from question 3?

**Question 7: ** The command `objdump -d main.o` allows you to disassemble the code and return to the assembler. Compare the output of the `objdump -d main.o` command with the main.s file. Are the assembler directives (the lines in the assembler file that start with a . such as ".toto") still present? Is the assembler the same for the "leaq" instruction (load equivalent address quadword).

Let's look at the main executable file:

**Question 8:** If we do `objdump -d main` and look at the "leaq" instruction, do we get the same result as in the assembler and the object file? 

The instruction leaq 21(%rip), %rdi (and its comment "## 0x100003f85 <_printf+0x100003f85>") loads the contents of address 0x100003f85 into printf. 

**Question 9:** What does a hexdump -C main` find at address 0x000003f85? Note: the offset of 0x100000000 has been ignored because the hexdump does not display the addresses as the program will be loaded when it is executed.

## 2 Introduction to makefiles

In this second part, we will look at the benefits of using makefiles to compile a project. In a real project, it is rare to have a single source file; more often than not, you end up with :
- A tree structure with several folders containing all the source files
- Source files
- Header files

Let's look at the following small project:
- A src folder containing main.c and operations.c
- An inc folder containing header.h and operation.h
- A build folder containing the compiled files

If you want to compile this project, you need to :
1. Compile the main.c file into main.o
2. Compile the operations.c file into operations.o
3. Link the two files together and produce the project executable.

To compile main.c and operations.c, you also need to include the headers files. To do this, add "-I {includesfolderpath}" at compile time.
To compile this project, you need to do :
1. `gcc -c src/main.c -Iinc -o build/main.o`
2. `gcc -c src/operations.c -Iinc -o build/operation.o`
3. `gcc build/main.o build/operation.o -o build/program`
You can then run the program by doing `./build/program`. 

It's easy to see that compiling a program with dozens or even hundreds of files can quickly become a nightmare. This is why the make tool was invented to automate compilation.

Nous allons voir comment creer un fichier Makefile pour compiler le projet. Un makefile est basé sur ce qu'on appelle des "cibles" ou "targets" en anglais. La syntaxe est la suivante : 
```
cible : composantes
    commandes
```
Chaque cible est definie par des composantes et des commandes (Remarques : une cible peut avoir 0 composante et 0 commande même si cela ne serait pas très utile).
- A component is a dependency of the target, and can be a file or another target. For the target to be realised, it is necessary that 
    - The file exists if the component is a file
    - The target has been executed.
- A command is, as its name suggests, a command to be executed if all the components are present or have been executed.

**Question 1:** Fill in the Makefile with the following targets.Which echo command will be executed first and why? Run the `make` command and confirm (or disprove) your theory.
```
test1 : test2
	@echo "Echo from test 1"

test2 :
	@echo "Echo from test 2"
```

**Note:** The @ before echo mutes the command call. Only the output of the command appears. If the @ was not present then the terminal would display 
```
> echo "Echo from test 2"
> Echo from test 2
```

In reality, when the `make` command is executed, the makefile tool will automatically execute the first target of the Makefile (or makefile) present in the directory. But you can execute a target other than the first one in the file. All you have to do is `make targetname`.

**Question 2:** Run the command `make test2`, which target is called? Is test1 called? Why or why not?

If you want to run a Makefile which is not called Makefile or makefile, you need to run `make -f filename`. But it is conventional to name the main Makefile Makefile (without extension).

A Makefile can include other Makefiles, this is a method often used to avoid ending up with one gigantic Makefile but several makefiles, each specialised for one action. It is generally accepted that these secondary makefiles have the .mk extension at the end of the file name. To include a makefile in a makefile, simply write `include makefilename`.

A common use for secondary makefiles is the path.mk file, in which all the project paths are stored as variables.

To create a variable in a makefile, simply write :
``` NAMEVARIABLE = variablevalue ```
To use this variable in the makefile, just do 
``` $(VARIABLENAME) ```

The paths.mk file has been prepared with the WORKSPACE_DIR, SRC_DIR, INC_DIR and BUILD_DIR variables.

**Question 3:** Modify the Makefile written above so that test1 prints the path to the build folder and test2 prints the path to the sources and includes.
The output should be 
```
> Source path: ./src
> Includes path: ./inc
> Build path: ./build
```

**Question 4 : ** Delete the test1 and test2 targets and replace them with 3 targets : \$(BUILD_DIR)/program, \$(BUILD_DIR)/main.o, \$(BUILD_DIR)/operations.o. For each target indicate the good components and the commands.

**Question 5:** Add two targets: build and clean. The build target must be the first target in the makefile and has the component \$(BUILD_DIR)/program and no commands. Whereas clean has no component and the command `rm -rf build/*`.

We can now do `make clean build`. You can even create an all target with clean and build components.

From here we should end up with the following Makefile:
```
include path.mk

all : clean build

build : $(BUILD_DIR)/program

$(BUILD_DIR)/program : #Place dependencies
	#Put the command

$(BUILD_DIR)/main.o : #Set dependencies
	#Put the command

$(BUILD_DIR)/operations.o : #Set dependencies
	#Put the command

clean :
	rm -rf build/*
```

Rather than having to copy the target and dependencies into the command, you can use "\$^" instead of the components and "\$@" instead of the target. For example 

```
toto.o : toto.c
    gcc -c toto.c -o toto.o
```
Becomes :
```
toto.o : toto.c
    gcc -c $^ -o $@
```

**Question 6:** Modify the makefile so that commands only use \$^ and \$@.

You can see that the main.o and operations.o targets have exactly the same command `gcc -c $^ -I$(INC_DIR) -o $@`. We could therefore use a way of creating a generic target for all object files. To do this, we use the % operator, which is equivalent to "for any element".
For example :
```
$(PDF_DIR)/%.pdf : $(TXT_DIR)/%.txt
    #txt to pdf conversion command
```
Is a generic target for generating a pdf based on a text file.

**Question 7:** Replace the targets \$(BUILD_DIR)/main.o and \$(BUILD_DIR)/operations.o with a single target using %.

You should then end up with the following makefile:
```
include path.mk

all : clean build

build : $(BUILD_DIR)/program

$(BUILD_DIR)/program : #list of .o files
	gcc $^ -o $@

# cible_o_generique : component_c_generique
    gcc -c $^ -I$(INC_DIR) -o $@

clean :
	rm -rf build/*
```

There's one last problem we'd like to solve: for the target program, we end up having to list all the object files in the components. We would like to have a variable which automatically contains the object files.
We therefore propose to create an SRCS variable containing all the source files and an OBJS variable containing all the OBJS files.

**Question 8:** Create the variable SRCS by listing all the source files in it. Then create the OBJS variable by doing `OBJS = $(SRCS:.c=.o)` (This means that you take all the elements of SRCS and change the .c extension to .o). Modify the makefile accordingly.

For the moment we have only shifted the problem: instead of having the list of object files in the target \$(BUILD_DIR)/program we have it in the SRCS variable. You can then use the `wildcard *` command, which lists all the elements in the current directory. To make SRCS contain all the source files in the src folder, just do `SRCS = $(wildcard $(SRC_DIR)/*.c)`.

**Question 9:** Modify the makefile accordingly.

You can even create a TARGET variable which contains the target (here \$(BUILD_DIR)/program) and replace \$(BUILD_DIR)/program by target which will be more aesthetic.

A nice makefile at the end of this exercise should look like the following:
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
