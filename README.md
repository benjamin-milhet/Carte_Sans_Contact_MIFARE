# TP_Carte_Sans_Contact

## Introduction
Le but de ce TP est  le développement d'une interface graphique pour un lecteur de carte
sans contact Mifare Classic. Le développement se fera avec QT Creator et nous disposons d'une 
librairie fournie permettant d'utiliser les fonctions associées au lecteur de carte.
L'application doit permettre la connexion entre une carte et le lecteur.
L'interface graphique doit comprendre des fonctionnalités permettant d'afficher et de modifier
les informations d'identité du processeur de la carte. On souhaite également pouvoir gérer
un porte-monnaie et un système d'incrément et de décrément d'unités contenues dans le dit
porte-monnaie.

## Connexion du lecteur de carte
La fonction "on_Connect_clicked", qui s'appelle lors de l'appuie sur le bouton "Se connecter", permet de se connecter au lecteur de carte avec la fonction "OpenCOM" issue de la librairie fournit. Ensuite nous vérifions que celui c'est bien connecter avec la variable status, puis nous pouvons récupérer sa version et permettre de nouvelle action sur l'interface graphique.

## Deconnexion du lecteur de carte
La fonction "on_Deconnect_clicked" permet de déconnecter le lecteur de carte avec la fonction "CloseCOM" de la librairie.

## Lecture d'une carte
La fonction "on_connectCarte_clicked" s'active lors de l'activation du bouton "Sélectionner la carte" sur l'interface graphique et permettant la lecture du contenu d'une carte. 

## Buzzer et led
La fonction "tag_hat" et une fonction reprise de la documentation fournie permettant lors de son appel de faire "bipper" le buzzer et d'allumer les LEDs.

## Quitter
La fonction "on_Quitter_clicked" est une fonction qui ferme l'application lorsque l'on clique sur le bouton quitter.

## Conversions
Les fonctions "convertirIntToQstring" et "convertirQstringToChar"  sont des fonctions convertissent respectivement un en entier en Qstring et une Qstring en char.
ces deux fonction permettent des conversions de type qui nous seront utiles lors de l'écriture de données dans la carte.

## Affichage des informations
La fonction "on_connectCarte_clicked" est la fonction qui permet d'afficher les informations contenues dans la carte.
Tout d'abord on rentre dans une condition qui vérifie que le statut et bon ce qui signifie qu'une carte est bien posée sur le lecteur et que l'on peut lire ses données.
Si la condition est vérifié on passe les boutons de saisie, d'incrément et décrément en "enable". Il est donc à présent possible d'écrire et de modifier la valeur du porte monnaie. Ensuite on utilise la fonction  Mf_Classic_Read_Block pour lire le prénom et le nom dans les bon blocs. Enfin on appelle la fonction update pour mettre à jour l'affichage.
Si la condition sur le statut n'était pas vérifié les boutons seraient restés désactivés et le message "Erreur lecture carte" se serait affiché dans les zones des saisie.

## Ecriture du Nom et du Prenom
La fonction "on_Saisie_clicked" permet d'enregistrer dans la carte les informations écrites par l'utilisateur dans les cases de saisie du nom et du prénom.
Avant toute chose on vérifie que le statu est bon ensuite on place dans des variables les Qstrings saisie et enfin on écrit dans les blocs correspondants an nom et prénom les variables correspondantes.
Si la condition sur le statut n'était pas vérifiée on affiche "Erreur lecture carte" sur la fenêtre de saisie et on enregistre aucune information.

## Incrément et Décrément
La fonction "on_incrementButton_clicked" utilise les fonctions Mf_Classic_Increment_Value et Mf_Classic_Restore_Value pour incrémenter la valeur du porte-monnaie et enregistrer cette valeur dans un bloc de backup de la carte lorsque l'on clique sur le bouton. Idem avec pour la fonction on_decrementButton_clicked pour le décrément.

## Actualisation de l'incrément
La fonction "actualiserIncrement" permet d'actualiser la valeur du porte-monnaie lorsque l'on souhaite incrémenter ou décrémenter.

## Lecture du porte monnaie
La fonction "getNbUniteRestante" permet de retourner la valeur du porte monnaie en allant chercher l'information contenue dans la carte grâce à la fonction "Mf_Classic_Read_Value".

## Son de lancement
En bonus nous avons créer une petit son de lacement lorsque la carte se connecte. Il s'agit de la fonction "MelodyBuzzer".
