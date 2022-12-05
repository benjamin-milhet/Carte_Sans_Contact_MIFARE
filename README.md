# TP_Carte_Sans_Contact

## Introduction
Le but de ce TP est  le développement d'une interface graphique pour un lecteur de carte
sans contact Mifare Classic. Le développement se fera avec QT creator et nous dispon d'une 
librairie fournie permettant d'utiliser les fonctions associées au lecteur de carte.
L'application doit permettre la connexion entre une carte et le lecteur.
L'interface graphique doit comprendre des fonctionnalités permettant d'afficher et de modifier
les informations d'identité du pocesseur de la carte. On souhaite également pouvoir gerer
un porte-monnaie et un système d'incrément et de décrement d'unitées contenues dans le dit
porte-monnaie.

## Connexion du lecteur de carte
La fonction "on_Connect_clicked", qui s'appelle lors de l'appuie sur le bouton "Se connecter", permet de se connecter au lecteur de carte avec la fonction "OpenCOM" issue de la librairie fournit. Ensuite nous vérifions que celui c'est bien connecter avec la variable status, puis nous pouvons récupérer sa version et permetre de nouvelle action sur l'interface graphique.

## Deconnexion du lecteur de carte
La fonction "on_Deconnect_clicked" permet de déconnecter le lecteur de carte avec la fonction "CloseCOM" de la librairie.

## Lecture d'une carte
La fonction "on_connectCarte_clicked" s'active lors de l'activation du bouton "Sélectionner la carte" sur l'interface graphique et permettant la lecture du contenu d'une carte. 
