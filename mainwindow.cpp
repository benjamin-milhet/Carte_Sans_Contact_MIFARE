#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "MfErrNo.h"
#include "Core.h"
#include "Sw_Device.h"
#include "Sw_Mf_Classic.h"
#include "Sw_Poll.h"
#include "Sw_ISO14443A-3.h"
#include "TypeDefs.h"
#include "Tools.h"

#include <QtGui>

ReaderName MonLecteur; // Variable representant le lecteur de carte

BOOL bench = FALSE; // Variable permettant de savoir si on est en mode bench ou non

int16_t status = MI_OK; // Status en cours initialisé à MI_OK qui est une valeur de réussite
uint8_t i; 
char s_buffer[64];
uint8_t atq[2];
uint8_t sak[1];
uint8_t uid[12];
uint16_t uid_len = 12;
uint8_t sect_count = 0;

// Constructeur de la fenêtre principale
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("ODALID"); // Titre de la fenêtre
}

// Destructeur de la fenêtre principale
MainWindow::~MainWindow()
{
    delete ui;
}

// Fonction permettant de connecter le lecteur de carte
void MainWindow::on_Connect_clicked() {

    int16_t status = MI_OK;
    MonLecteur.Type = ReaderCDC; // Type de lecteur de carte
    MonLecteur.device = 0; // Numéro du lecteur de carte
    status = OpenCOM(&MonLecteur); // Etablissement de la connexion avec le lecteur de carte

    status = Version(&MonLecteur); // Récupération de la version du lecteur de carte
    if (status == MI_OK){ // Si la connexion est réussie
         ui->Connect->setEnabled(FALSE); // On désactive le bouton de connexion
         status = LEDBuzzer(&MonLecteur, LED_YELLOW_ON); // Allumage de la LED jaune

         // RF field ON
         RF_Power_Control(&MonLecteur, TRUE, 0); 

         ui->Affichage->setText(MonLecteur.version); // Affichage de la version du lecteur de carte
         ui->Affichage->update(); // Mise à jour de l'affichage

         this->MelodyBuzzer(); // Jouer une mélodie avec le buzzer

         ui->connectCarte->setEnabled(TRUE); // Activation du bouton de connexion avec la carte
         ui->Deconnect->setEnabled(TRUE); // Activation du bouton de déconnexion du lecteur de carte

    }
}

// Fonction permettant de deconnecter le lecteur de carte
void MainWindow::on_Deconnect_clicked()
{
    RF_Power_Control(&MonLecteur, FALSE, 0);
    status = LEDBuzzer(&MonLecteur, LED_OFF); // Eteindre la LED
    status = CloseCOM(&MonLecteur); // Fermeture de la connexion avec le lecteur de carte

    if (status == MI_OK) { // Si la déconnexion est réussie
        ui->Connect->setEnabled(TRUE); // Activation du bouton de connexion
        ui->Deconnect->setEnabled(FALSE); // Désactivation du bouton de déconnexion
        ui->connectCarte->setEnabled(FALSE); // Désactivation du bouton de connexion avec la carte


        ui->Affichage->setText("Lecteur déconnecté"); // Texte affichant que le lecteur est déconnecté
        ui->Affichage->update(); // Mise à jour de l'affichage
    }
}

// Fonction permettant de faire un bruit de buzzer de validation
void MainWindow::tag_hat(){
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON+LED_YELLOW_ON+LED_RED_ON+LED_GREEN_ON);
    DELAYS_MS(100);
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON);
}

// Fonction permettant de quitter l'application
void MainWindow::on_Quitter_clicked()
{
    int16_t status = MI_OK;
    RF_Power_Control(&MonLecteur, FALSE, 0);
    status = LEDBuzzer(&MonLecteur, LED_OFF); // Eteindre la LED
    status = CloseCOM(&MonLecteur); // Fermeture de la connexion avec le lecteur de carte
    qApp->quit(); // Fermeture de l'application
}

// Fonction permettant de convertir un entier en QString
QString MainWindow::convertirIntToQstring(int monEntier){
    return QString::number(monEntier);
}

// Fonction permettant de convertir un QString en uint8_t
uint8_t* MainWindow::convertirQstringToChar(QString DataText) {
    char DataIn[240];
    sprintf(DataIn, DataText.toUtf8().data(), 240);
    qDebug() << (uint8_t*)DataIn;
    return (uint8_t*)DataIn;
}

// Fonction permettant de récuperer les informations d'une carte MIFARE
void MainWindow::on_connectCarte_clicked()
{
     status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len); // Vérification qu'une carte est présente

     if (status == MI_OK){ // Si une carte est présente
         ui->Saisie->setEnabled(TRUE); // Activation du bouton de saisie
         ui->incrementButton->setEnabled(TRUE); // Activation du bouton d'incrémentation
         ui->decrementButton->setEnabled(TRUE); // Activation du bouton de décrémentation

         uint8_t dataPrenom[16];
         status = Mf_Classic_Read_Block(&MonLecteur, TRUE, 9, dataPrenom, AuthKeyA, 2); // Lecture du prénom

         uint8_t dataNom[16];
         status = Mf_Classic_Read_Block(&MonLecteur, TRUE, 10, dataNom, AuthKeyA, 2); // Lecture du nom


         ui->nom->setText((char*)dataNom); // Affichage du nom
         ui->nom->update(); // Mise à jour de l'affichage

         ui->prenom->setText((char*)dataPrenom); // Affichage du prénom
         ui->prenom->update(); // Mise à jour de l'affichage

         ui->Affichage->setText("Carte détectée"); // Affichage du texte "Carte détectée"
         ui->Affichage->update(); // Mise à jour de l'affichage

        this->actualiserIncrement(); // Actualisation de l'incrémentation

        this->tag_hat(); // Jouer un bruit de buzzer de validation
     } else { // Si aucune carte n'est présente
         ui->nom->setText("Erreur lecture carte"); // Affichage du texte "Erreur lecture carte"
         ui->nom->update(); // Mise à jour de l'affichage

         ui->prenom->setText("Erreur lecture carte"); // Affichage du texte "Erreur lecture carte"
         ui->prenom->update(); // Mise à jour de l'affichage

         ui->nbUnite->setPlainText("Erreur lecture carte"); // Affichage du texte "Erreur lecture carte"
         ui->nbUnite->update(); // Mise à jour de l'affichage

         ui->Affichage->setText("Erreur lecture carte"); // Affichage du texte "Erreur lecture carte"
         ui->Affichage->update(); // Mise à jour de l'affichage

         ui->Saisie->setEnabled(FALSE); // Désactivation du bouton de saisie
         ui->incrementButton->setEnabled(FALSE); // Désactivation du bouton d'incrémentation
         ui->decrementButton->setEnabled(FALSE); // Désactivation du bouton de décrémentation
     }
}

// Fonction permettant d'actualiser les informations d'une carte MIFARE
void MainWindow::on_Saisie_clicked()
{
    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len); // Vérification qu'une carte est présente

    if (status == MI_OK) { // Si une carte est présente
        QString nomText = ui->nom->toPlainText(); // Récupération du nom
        QString prenomText = ui->prenom->toPlainText(); // Récupération du prénom

        char DataInPrenom[16];
        sprintf(DataInPrenom, prenomText.toUtf8().data(), 16); // Conversion du prénom en char
        auto dataPrenom = (uint8_t*)DataInPrenom;

        char DataInNom[16];
        sprintf(DataInNom, nomText.toUtf8().data(), 16); // Conversion du nom en char
        auto dataNom = (uint8_t*)DataInNom;

        status = Mf_Classic_Write_Block(&MonLecteur, TRUE, 9, dataPrenom, AuthKeyB, 2); // Ecriture du prénom dans la carte
        status = Mf_Classic_Write_Block(&MonLecteur, TRUE, 10, dataNom, AuthKeyB, 2); // Ecriture du nom dans la carte 

        this->tag_hat(); // Jouer un bruit de buzzer de validation
    } else { // Si aucune carte n'est présente
        ui->Affichage->setText("Erreur lecture carte"); // Affichage du texte "Erreur lecture carte"
        ui->Affichage->update(); // Mise à jour de l'affichage
    } 
}

// Fonction permettant d'actualiser l'incrémentation
void MainWindow::on_incrementButton_clicked()
{
    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len); // Vérification qu'une carte est présente
    if (status == MI_OK) { // Si une carte est présente
        auto dataCompteur = ui->increment->value(); // Récupération de la valeur de l'incrémentation
        status = Mf_Classic_Increment_Value(&MonLecteur, TRUE, 14, dataCompteur, 13, AuthKeyB, 3); // Incrémentation de la valeur du compteur
        status= Mf_Classic_Restore_Value(&MonLecteur, TRUE, 13, 14, AuthKeyA, 3); // Restauration de la valeur du compteur

        this->actualiserIncrement(); // Actualisation de l'incrémentation

        this->tag_hat(); // Jouer un bruit de buzzer de validation
    } else { // Si aucune carte n'est présente
        ui->Affichage->setText("Erreur lecture carte"); // Affichage du texte "Erreur lecture carte"
        ui->Affichage->update(); // Mise à jour de l'affichage
    }
}

// Fonction permettant d'actualiser la décrémentation
void MainWindow::on_decrementButton_clicked()
{
    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len); // Vérification qu'une carte est présente
    if (status == MI_OK) { // Si une carte est présente
        auto dataCompteur = ui->decrement->value(); // Récupération de la valeur de la décrémentation
        status = Mf_Classic_Decrement_Value(&MonLecteur, TRUE, 14, dataCompteur, 13, AuthKeyA, 3); // Décrémentation de la valeur du compteur
        status= Mf_Classic_Restore_Value(&MonLecteur, TRUE, 13, 14, AuthKeyA, 3); // Restauration de la valeur du compteur

        this->actualiserIncrement(); // Actualisation de la décrémentation

        this->tag_hat(); // Jouer un bruit de buzzer de validation
    } else { // Si aucune carte n'est présente
        ui->Affichage->setText("Erreur lecture carte"); // Affichage du texte "Erreur lecture carte"
        ui->Affichage->update(); // Mise à jour de l'affichage
    }
}

// Fonction permettant d'actualiser l'affichage de la valeur du compteur
void MainWindow::actualiserIncrement(){
    ui->nbUnite->setPlainText(this->convertirIntToQstring(this->getNbUniteRestante())); // Actualisation de l'affichage de la valeur du compteur
    ui->nbUnite->update(); // Mise à jour de l'affichage
}

// Fonction permettant de récupérer la valeur du compteur dans la carte
int MainWindow::getNbUniteRestante(){
    uint32_t dataCompteur = 0; // Initialisation de la variable dataCompteur
    status = Mf_Classic_Read_Value(&MonLecteur, TRUE, 14, &dataCompteur, AuthKeyA, 3); // Lecture de la valeur du compteur

    return dataCompteur; // Retourne la valeur du compteur
}

// Fonction permettant de jouer une petite mélodie de buzzer
void MainWindow::MelodyBuzzer() {
    for (int i = 5; i > 0 ; i--) {
        status = LEDBuzzer(&MonLecteur, LED_GREEN_ON+LED_YELLOW_ON+LED_RED_ON+LED_GREEN_ON);
        DELAYS_MS(30*i);
        status = LEDBuzzer(&MonLecteur, LED_GREEN_ON);
        DELAYS_MS(30*i);
        status = LEDBuzzer(&MonLecteur, LED_GREEN_ON+LED_YELLOW_ON+LED_RED_ON+LED_GREEN_ON);
        DELAYS_MS(15*i);
        status = LEDBuzzer(&MonLecteur, LED_GREEN_ON);
        DELAYS_MS(30*i);
    }
}


