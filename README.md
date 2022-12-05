# TP_Carte_Sans_Contact

## Introduction

## Connexion du lecteur de carte
La fonction "on_Connect_clicked", qui s'appelle lors de l'appuie sur le bouton "Se connecter", permet de se connecter au lecteur de carte avec la fonction "OpenCOM" issue de la librairie fournit. Ensuite nous vérifions que celui c'est bien connecter avec la variable status, puis nous pouvons récupérer sa version et permetre de nouvelle action sur l'interface graphique.

## Deconnexion du lecteur de carte
La fonction "on_Deconnect_clicked" permet de déconnecter le lecteur de carte avec la fonction "CloseCOM" de la librairie.

## Lecture d'une carte
La fonction "on_connectCarte_clicked" s'active lors de l'activation du bouton "Sélectionner la carte" sur l'interface graphique et permettant la lecture du contenu d'une carte. 
