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
- Interface : I2C (adresse par défaut 0x90)
- Feature : Overtemperature Detector (pin OS du capteur)

Le LM75 est un capteur de temperature digital possédant un detecteur de surtemperature, ce qui permet au capteur de piloter un système de ventilation ou un système d'alarme sans à avoir à utiliser un microntrolleur (sauf pour programmer le capteur). Dans notre cas nous utiliserons cette feature pour detecter une surtemperature dans la section suivante.

En I2C, le LM75 peut être vu comme une mémoire contenant 4 registres :
| Nom du Registre | Adresse | Etat par Défaut | Droit |
|-----------------|---------|-----------------|-------|
| Temperature     | 0x00    | 0x0000          | RO    |
| Configuration   | 0x01    | 0x00            | RW    |
| T_HYST          | 0x02    | 0x4B00          | RW    |
| T_OS            | 0x03    | 0x5000          | RW    |

Les registres Configuration, T_HYST et T_OS sont configurables (accès lecture/écriture) tandis que Temperature est accessible en lecture seule.

Les registres de Temperature, T_HYST et T_OS correspondent à des temperatures. Temperature correspond à la température actuelle, T_HYST correspond à la temperature de seuil bas du detecteur de surtempérature et T_OS correspond à la temperature de seuil haut du detecteur c-à-d que si la temperature depasse T_OS alors la pin OS vaut 0 et si la temperature passe en dessous de T_HYST alors la pin OS vaut 1 (système d'hysteresie voir Figure 1. de la datasheet).
Les températures stockées sont définis de la manière suivante :
| D15   | D14  | 13   | D12  | D11 | D10 | D9  | D8  | D7    | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
|-------|------|------|------|-----|-----|-----|-----|-------|----|----|----|----|----|----|----|
| Signe | 64°C | 32°C | 16°C | 8°C | 4°C | 2°C | 1°C | 0.5°C | X  | X  | X  | X  | X  | X  | X  |

Le registre Configuration contient les bits suivants :
| D7 | D6 | D5 | D4          | D3          | D2          | D1      | D0       |
|----|----|----|-------------|-------------|-------------|---------|----------|
| 0  | 0  | 0  | Fault Queue | Fault Queue | OS Polarity | OS Mode | ShutDown |

Les registres Fault Queue déterminer le nombre de fautes nécessaires pour déclencher une condition d'OS (0b00 = 1, 0b01 = 2, 0b10 = 4, 0b11 = 6). OS Polarity indique si la pin OS est active à l'état bas (OS Polarity = 0b0) ou active à l'état haut (OS Polarity = 0b1). OS Acquisition Mode indique si on est en mode :
- Comparateur : Si la témperature passe au dessus de T_OS alors la pin OS est active (0 par défaut), si la temperature passe sous T_HYST alors la pin OS est passive (1 par défaut).
- Interrupt : L'état de la pin OS est fait uniquement lorsque le capteur lit la donnée de température.
On utilisera le mode comparateur.

**Question 1:** Dans le fichier LM75_driver.c dans la section Macro definition, définir les constantes suivantes : TEMP_REG_ADDR, CONF_REG_ADDR, T_HYST_REG_ADDR, T_OS_REG_ADDR avec les addresses des 4 registres comme défini plus haut. Puis, toujours dans le fichier LM75_driver.c définir FAULT_QUEUE_OFFSET, FAULT_QUEUE_MASK, OS_POLARITY_OFFSET, OS_POLARITY_MASK, OS_MODE_OFFSET, OS_MODE_MASK, SHUTDOWN_OFFSET, SHUTDOWN_MASK.

**Remarque :** On choisit de placer les #define dans le fichier C au lieu du fichier H, cela permet que ces #define ne sont accessible qu'aux éléments définis dans le fichier LM75_drv.c et non tous les fichiers qui inclurait LM75_drv.h. 

D'une manière générale il faut faire attention au scope de définition des macros, variables, fonctions. Il faut toujours les definir dans le scope le plus réduit possible. Cela permet de "privatiser" les macros, variables, fonctions et de réduire les interfaces entre les divers codes à quelques macros, variables, fonctions.

On remarque que pour lire ou ecrire dans le LM75 on effectue toujours les mêmes transactions :
- En lecture : On commence par un écriture I2C dans laquelle on indique l'addresse du **registre** que l'on souhaite lire (sous entendu que l'addresse de l'esclave est envoyé au début de la trame). Puis on fait une lecture I2C pour lire le contenu du registre (de 1 ou 2 octets)
- En écriture : On effectue une écriture I2C dans laquelle on commence par indiquer l'addresse du **registre** que l'on souhaite modifier (sous entendu que l'addresse de l'esclave est envoyé au début de la trame), puis sur la même transaction on transmet le contenu du registre (de 1 ou 2 octets). 
C'est pourquoi on propose d'écrire des fonctions générique pour repondre à ce besoin.

**Question 2:** Ecrire la fonction LM75GetReg qui lit le contenu d'un registre. La fonction doit avoir la déclaration suivante :
```
static equipmentsStatus_t LM75GetReg(int8_t reg_addr,int8_t *content, uint8_t size);
```
Cette fonction doit effectuer une écriture puis une lecture. Il faut que la taille de la lecture soit dependente de l'addresse (en gros si l'addresse = CONF_REG_ADDR on ne lit qu'un octet), on pourra faire de la verification sur l'argument size et retourner EQUIPMENTS_INVALID_PARAM si la taille n'est pas coherente au registre que l'on souhaite lire.
De plus, la fonction être déclarer de manière a rester dans le scope du driver LM75 (délimité par le fichier LM75_drv.c), c'est pourquoi on ajoute l'attribut *static* devant la fonction pour indiquer que la fonction a une portée limitée à son fichier source. La déclaration de la fonction doit se faire dans le fichier .c (dans la catégorie "Functions Declarations") sinon l'attribut static n'a aucun sens.

**Question 3:** De même que pour LM75GetReg, écrire la fonction LM75SetReg qui lit le contenu d'un registre. La fonction doit avoir la déclaration suivante :
```
static equipmentsStatus_t LM75SetReg(int8_t reg_addr,int8_t *content, uint8_t size);
```

**Question 4:** Creer une fonction LM75ReadTemperature qui lit la temperature du LM75. La fonction doit avoir la déclaration suivante :
```
equipmentsStatus_t LM75ReadTemperature(int8_t *temperature);
```
La fonction doit retourner un code d'erreur de type equipmentsStatus_t (défini dans equipements_type.h) en fonction de si une erreur à eu lieu ou non. La temperature doit être passer en tant pointeur. On oubliera pas de **déclarer** la fonction dans le header (.h) et de **définir** la fonction dans le fichier source (.c) car cette fois ci la fonction est destiné à être utilisée en dehors du driver.

**Remarque :** Il est mieux que toute fonction utilise le retour pour rendre compte de son status et non retourner les data d'ouput. Cela permet d'evalue si la fonction s'est bien executer, de plus passer outputs en variable pointeurs permet de ne pas se limiter à une variable.

**Question 5:** Creer une fonction LM75SetOSTemperatures qui regles les temperatures T_HYST et T_OS. La fonction doit avoir la déclaration suivante :
```
equipmentsStatus_t LM75SetOSTemperatures(int8_t t_hyst, int8_t t_os);
```
Cette fonction doit regler la temperature T_HYST **et** T_OS (l'ordre n'a pas d'importance) donc 2 transactions sont requises.

**Question 6:** De même creer une fonction LM75GetOSTemperatures qui obtient les valeurs de T_HYST et T_OS. La fonction doit avoir la déclaration suivante :
```
equipmentsStatus_t LM75GetOSTemperatures(int8_t *t_hyst, int8_t *t_os);
```

**Question 7:** Creer un type structure lm75Conf_t qui contient les quatres éléments de la configuration du capteur : fault_queue, os_polarity, os_mode, shutdown. On utilisera des uint8_t pour stocker chacun des champs.

**Question 8:** Creer une fonction LM75GetConf qui regles la configuration du LM75.
```
equipmentsStatus_t LM75GetConf(lm75Conf_t *lm75_conf);
```

**Question 9:** Creer une fonction LM75SetConf qui regles la configuration du LM75.
```
equipmentsStatus_t LM75SetConf(lm75Conf_t lm75_conf);
```

Jusqu'ici nous avons couvert la plupart des fonctions utiles pour utiliser le LM75 néanmoins nos fonctions ne marche que s'il n'y a qu'un seul capteur et/ou qu'un seul bus I2C. On propose alors de creer une instance (un peu à la manière d'un objet en programmation orienté objet) qui est une structure qui sera passé dans chacune des fonctions du driver et qui permet de passer les parametres de bus et capteur.

On propose la structure suivante :
```
/** 
 * @struct  lm75Inst_t
 * @brief   Struct type definition of a LM75 instance
 */
typedef struct
{
    iicInst_t *iic_instance;    /**< @brief Pointer to the I2C instance with whom the LM75 is connected to */
    iicSlaveAddr_t sensor_addr; /**< @brief LM75 I2C address */
} lm75Inst_t;
```

**Question 10:** Modifier toutes les fonctions du driver LM75 de façon à faire passer en temps que pointeur l'instance lm75. On propose les déclarations suivantes :
```
// Dans le fichier .c
static equipmentsStatus_t LM75GetReg(int8_t reg_addr,int8_t *content, uint8_t size);
static equipmentsStatus_t LM75SetReg(int8_t reg_addr,int8_t *content, uint8_t size);
// Dans le fichier .h
equipmentsStatus_t LM75ReadTemperature(int8_t *temperature);
equipmentsStatus_t LM75SetOSTemperatures(int8_t t_hyst, int8_t t_os);
equipmentsStatus_t LM75GetOSTemperatures(int8_t *t_hyst, int8_t *t_os);
equipmentsStatus_t LM75GetConf(lm75Conf_t *lm75_conf);
equipmentsStatus_t LM75SetConf(lm75Conf_t lm75_conf);
```

## 3. Gestion de l'Overtemperature Output

## 4. Programmation du système

## 5. Standard de programmation : MISRA C

Pour des raisons de copyrights, je ne peux pas dans cette partie fournir une copie du standard MISRA C. Si cette exercice est réalisé en presentiel et que je suis présent, nous pouvons réaliser cette section ensemble. Si ce n'est pas le cas et que vous ne possedez pas une copie des guidelines du MISRA C je vous invite à sauter cette section.

**Question X:** Executer la commande `make verif`, quelles sont sont les types d'erreurs qui ont été commise (Entre crochet à la fin de l'erreur). 

**Question X:** Corriger les erreurs jusqu'à qu'il n'y ai plus d'erreur detectées par cppcheck. On pourra dans le cas de faux positif ajouter le commentaire "// cppcheck-suppress nomerreur" sur la ligne qui declenche un faux positif.

**Question X:** On peut également verifier que la documentation a bien été rediger en executant le script update-doc.sh.
