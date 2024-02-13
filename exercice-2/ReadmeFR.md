# Exercice 2 : Programmation embarquée

Dans cette exercice nous allons introduire les concepts de la programmation embarqué en bare metal. L'idée etant de se concentré sur la programmation bare metal autour d'un use case basé sur le LM75. Nous allons voir nottament :
- Le concept de driver équipement, comment rediger un driver. Quels sont les bons formalismes à adopter
- Le concept d'interruption, nottament en utilisant l'overtemperature output du LM75.
- Quels sont les standards à respecter en programmation embarquée.

La programmation de driver bas niveau n'est pas couvert par cette exercice. C'est un exercice long et fastidieux surtout pour les microcontrolleurs assez imposants comme les STM32H7. Je recommande de s'entrainer sur des processeurs AVR 8 bits pour coder des drivers bas niveau. 

## 1. Use Case

Dans cette exercice nous allons programmer en bare metal un système de controle de température. Le cahier des charges est le suivant :
- La temperature doit être mesurée toutes les secondes et stocké en interne.
- Entre chaque mesure de temperature le micro-controlleur doit se mettre en basse consommation.
- Un bouton doit permettre de dumper l'integralité des données via la liaison serie (uart print relié au STLINK).
- A tout moment, en cas de depassement d'un seuil de 30°, le système doit indiqué à l'aide d'un signal lumineux qu'une surtemperature est detectée.

## 2. Driver Equipement LM75

Dans cette partie l'objectif est de realiser un driver equipement pour le LM75. Nous proposons de nous limiter aux fichiers LM75_drv.h et LM75_drv.c dans cette partie. (On pourra cependant utiliser le main pour pouvoir tester les fonctions).

Le LM75 est un capteur de température qui possède les caracteristiques suivantes :
- Résolution : 9 bits (LSB = 0.5°C, 1 bit de signe)
- Gamme d'utilisation : -55°C à +125°C
- LSB
- Precision : ±2°C
- Interface : I2C 
- Feature : Overtemperature Detector (pin OS du capteur)

Le LM75 est un capteur de temperature digital possédant un detecteur de surtemperature, ce qui permet au capteur de piloter un système de ventilation ou un système d'alarme sans à avoir à utiliser un microntrolleur (sauf pour programmer le capteur). Dans notre cas nous utiliserons cette feature pour detecter une surtemperature dans la section suivante.

## 3. Gestion de l'Overtemperature Output

## 4. Programmation du système

## 5. Standard de programmation : MISRA C

Pour des raisons de copyrights, je ne peux pas dans cette partie fournir une copie du standard MISRA C. Si cette exercice est réalisé en presentiel et que je suis présent, nous pouvons réaliser cette section ensemble. Si ce n'est pas le cas et que vous ne possedez pas une copie des guidelines du MISRA C je vous invite à sauter cette section.

**Question X:** Executer la commande `make verif`, quelles sont sont les types d'erreurs qui ont été commise (Entre crochet à la fin de l'erreur). 

**Question X:** Corriger les erreurs jusqu'à qu'il n'y ai plus d'erreur detectées par cppcheck. On pourra dans le cas de faux positif ajouter le commentaire "// cppcheck-suppress nomerreur" sur la ligne qui declenche un faux positif.

**Question X:** On peut également verifier que la documentation a bien été rediger en executant le script update-doc.sh.
