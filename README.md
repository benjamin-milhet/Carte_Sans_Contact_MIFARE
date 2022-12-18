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

## Buzzer et led
La fonction "tag_hat" et une fonction reprise de la documenttion fourie permettant lors de son appel de fair "bipper" le buzzer et d'allumer les leds.

## Quitter
La fonction "on_Quitter_clicked" est une fonction qui ferme l'application lorsque l'on clique sur le boutton quitter.

##
Conversions
Les focntions "convertirIntToQstring" et "convertirQstringToChar"  sont des fonctions convertissent respectivement un en entier en Qstring et une Qstring en char.
ces deux fonction permettent des convertions de type qui nous seront utiles lors de l'ecriture de données dans la carte.

## Affichage des informations
La fonction "on_connectCarte_clicked" est la fonction qui permet d'afficher les informations contenues dans la carte.
Tout d'abord on rentre dans une condition qui verifie que le status et bon ce qui signifie qu'une carte est bien posée sur le lecteur et que l'on peut lire ses données.
Si la condition est verifiée on passe les bouttons de saisie, d'incrément et décrement en "enable". Il est donc à present possible d'ecrire et de modifier la valeur du porte monnaie. Ensuite on utilise la fonction  Mf_Classic_Read_Block pour lire le prenom et le nom dans les bon blocs. Enfin on appelle la fonction update pour mettre à jour l'affichage.
Si la condition sur le satus n'était pas verifiée les bouttons seraient restés desactivés et le message "Erreur lecture carte" se serait affiché dans les zones des saisie.




