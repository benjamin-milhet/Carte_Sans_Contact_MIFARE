# Carte sans contact - MIFARE

## Introduction
Le but de ce TP est le développement d'une interface graphique pour un lecteur de cartes sans contact Mifare Classic. Le développement se fera avec QT Creator et nous disposons d'une librairie fournie permettant d'utiliser les fonctions associées au lecteur de cartes. L'application doit permettre la connexion entre une carte et le lecteur. L'interface graphique doit comprendre des fonctionnalités permettant d'afficher et de modifier les informations d'identité du processeur de la carte. On souhaite également pouvoir gérer un porte-monnaie et un système d'incrément et de décrément d'unités contenues dans le dit porte-monnaie.

## Développement de l’interface graphique

### Visuelle de l’application finale

#### Vision globale

![alt text](https://github.com/benjamin-milhet/Carte_Sans_Contact_MIFARE/blob/main/accueil.png?raw=true)

#### Détails des différentes parties de l’application

![alt text](https://github.com/benjamin-milhet/Carte_Sans_Contact_MIFARE/blob/main/partie1.png?raw=true)

Cette partie comporte 3 boutons importants pour se connecter et de déconnecter du lecteur de cartes. Le premier bouton "Se connecter" permet de se connecter au lecteur de cartes. Le bouton "Se déconnecter" permet de se déconnecter du lecteur de cartes. Le troisième et dernier bouton "Sélectionner la carte" permet de récupérer les informations d'une carte sans contact. A droite, il y a une zone d'affichage qui nous permettant d'afficher la version du lecteur ou si nous rencontrons un problème lors de la lecture d'une carte. Tous les boutons sauf le bouton "Se connecter" sont désactiver au lancement de l'application et sont activés au moment où le lecteur de cartes est connecté.

![alt text](https://github.com/benjamin-milhet/Carte_Sans_Contact_MIFARE/blob/main/partie2.png?raw=true)

Sur cette interface sont affichés le nom et le prénom du propriétaire de la carte scanner. Il est possible d'éditer directement ces deux paramètres précédents et les mettre à jour en ayant la carte toujours sur le lecteur et d'appuyer sur le bouton "Mettre à jour".

![alt text](https://github.com/benjamin-milhet/Carte_Sans_Contact_MIFARE/blob/main/partie3.png?raw=true)

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

### Conversions

Les fonctions "convertirIntToQstring" et "convertirQstringToChar" sont des fonctions convertissent respectivement un en entier en Qstring et une Qstring en char. ces deux fonction permettent des conversions de type qui nous seront utiles lors de l'écriture de données dans la carte.

### Affichage des informations

La fonction "on\_connectCarte\_clicked" est la fonction qui permet d'afficher les informations contenues dans la carte. Tout d'abord on rentre dans une condition qui vérifie que le statut et bon ce qui signifie qu'une carte est bien posée sur le lecteur et que l'on peut lire ses données. Si la condition est vérifié on passe les boutons de saisie, d'incrément et décrément en "enable". Il est donc à présent possible d'écrire et de modifier la valeur du porte monnaie. Ensuite on utilise la fonction "Mf\_Classic\_Read\_Block" pour lire le prénom et le nom dans les bon blocs. Enfin on appelle la fonction update pour mettre à jour l'affichage. Si la condition sur le statut n'était pas vérifié les boutons seraient restés désactivés et le message "Erreur lecture carte" se serait affiché dans les zones des saisie.

### Ecriture du Nom et du Prénom

La fonction "on\_Saisie\_clicked" permet d'enregistrer dans la carte les informations écrites par l'utilisateur dans les cases de saisie du nom et du prénom. Avant toute chose on vérifie que le statut est bon, ensuite on place dans des variables les Qstrings saisient et enfin on écrit dans les blocs correspondants aux nom et prénom les variables correspondantes. Si la condition sur le statut n'était pas vérifiée on affiche "Erreur lecture carte" sur la fenêtre de saisie et on enregistre aucune information.

### Incrément et Décrément

La fonction "on\_incrementButton\_clicked" utilise les fonctions "Mf\_Classic\_Increment\_Value" et "Mf\_Classic\_Restore\_Value" pour incrémenter la valeur du porte-monnaie et enregistrer cette valeur dans un bloc de backup de la carte lorsque l'on clique sur le bouton. Idem avec pour la fonction "on\_decrementButton\_clicked" pour le décrément.

### Actualisation de l'incrément

La fonction "actualiserIncrement" permet d'actualiser la valeur du porte-monnaie lorsque l'on souhaite incrémenter ou décrémenter.

### Lecture du porte monnaie

La fonction "getNbUniteRestante" permet de retourner la valeur du porte monnaie en allant chercher l'information contenue dans la carte grâce à la fonction "Mf\_Classic\_Read\_Value".

### Son de lancement

En bonus nous avons créer un petit son de lancement lorsque la carte se connecte. Il s'agit de la fonction "MelodyBuzzer".

## Conclusion

Ce projet nous a permis d'approfondir nos connaissances avec le langage C++ et le framework Qt Creator et d'utiliser nos connaissances vues pendant les cours afin de réaliser une application visuelle permettant de contrôler un lecteur de cartes sans contact. Nous avions à notre disposition une librairie qui nous était nouvelle et nous devions chercher à travers sa documentation l'ensemble des fonctions qui nous a été utile pur mener à bien ce projet. Ce projet nous a permis de combiner les notions vues en cours et en TD sur le comportement et le fonctionnement des cartes MIFARE et le fonctionnement de leur mémoire.


