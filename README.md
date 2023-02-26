# Carte sans contact - MIFARE

## Introduction
Le but de ce TP est le développement d'une interface graphique pour un lecteur de cartes sans contact Mifare Classic. Le développement se fera avec QT Creator et nous disposons d'une librairie fournie permettant d'utiliser les fonctions associées au lecteur de cartes. L'application doit permettre la connexion entre une carte et le lecteur. L'interface graphique doit comprendre des fonctionnalités permettant d'afficher et de modifier les informations d'identité du processeur de la carte. On souhaite également pouvoir gérer un porte-monnaie et un système d'incrément et de décrément d'unités contenues dans le dit porte-monnaie.

## Développement de l’interface graphique

### Visuelle de l’application finale

#### Vision globale

#### Détails des différentes parties de l’application

Cette partie comporte 3 boutons importants pour se connecter et de déconnecter du lecteur de cartes. Le premier bouton "Se connecter" permet de se connecter au lecteur de cartes. Le bouton "Se déconnecter" permet de se déconnecter du lecteur de cartes. Le troisième et dernier bouton "Sélectionner la carte" permet de récupérer les informations d'une carte sans contact. A droite, il y a une zone d'affichage qui nous permettant d'afficher la version du lecteur ou si nous rencontrons un problème lors de la lecture d'une carte. Tous les boutons sauf le bouton "Se connecter" sont désactiver au lancement de l'application et sont activés au moment où le lecteur de cartes est connecté.

Sur cette interface sont affichés le nom et le prénom du propriétaire de la carte scanner. Il est possible d'éditer directement ces deux paramètres précédents et les mettre à jour en ayant la carte toujours sur le lecteur et d'appuyer sur le bouton "Mettre à jour".

Sur cette interface est affiché le nombre d'unité restante sur la carte scanner. Il est possible de renseigner une valeur pour incrémenter ou décrémenter celle-ci puis d'appuyer sur le bouton respectif tout en ayant la carte sur le lecteur.

### Connexion du lecteur de carte

La fonction "on\_Connect\_clicked", qui s'appelle lors de l'appuie sur le bouton "Se connecter", permet de se connecter au lecteur de carte avec la fonction "OpenCOM" issue de la librairie fournit. Ensuite nous vérifions que celui c'est bien connecter avec la variable status, puis nous pouvons récupérer sa version et permettre de nouvelle action sur l'interface graphique.

### Deconnexion du lecteur de carte

La fonction "on\_Deconnect\_clicked" permet de déconnecter le lecteur de carte avec la fonction "CloseCOM" de la librairie.

### Lecture d'une carte

La fonction "on\_connectCarte\_clicked" s'active lors de l'activation du bouton "Sélectionner la carte" sur l'interface graphique et permettant la lecture du contenu d'une carte.

### Buzzer et led

La fonction "tag\_hat" et une fonction reprise de la documentation fournie permettant lors de son appel de faire "bipper" le buzzer et d'allumer les LEDs.

### Quitter

La fonction "on\_Quitter\_clicked" est une fonction qui ferme l'application lorsque l'on clique sur le bouton quitter.

