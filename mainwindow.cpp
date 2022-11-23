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

ReaderName MonLecteur;

BOOL bench = FALSE;

int16_t status = MI_OK;
uint8_t i;
char s_buffer[64];
uint8_t atq[2];
uint8_t sak[1];
uint8_t uid[12];
uint16_t uid_len = 12;
uint8_t sect_count = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Connect_clicked() {

    int16_t status = MI_OK;
    MonLecteur.Type = ReaderCDC;
    MonLecteur.device = 0;
    status = OpenCOM(&MonLecteur);

    status = Version(&MonLecteur);
    if (status == MI_OK){
         ui->Connect->setEnabled(FALSE);
         ui->Deconnect->setEnabled(TRUE);
         status = LEDBuzzer(&MonLecteur, LED_YELLOW_ON);

         // RF field ON
         RF_Power_Control(&MonLecteur, TRUE, 0);

         ui->Affichage->setText(MonLecteur.version);
         ui->Affichage->update();
    }
}

void MainWindow::on_Deconnect_clicked()
{
    RF_Power_Control(&MonLecteur, FALSE, 0);
    status = LEDBuzzer(&MonLecteur, LED_OFF);
    status = CloseCOM(&MonLecteur);

    if (status == 0) {
        ui->Connect->setEnabled(TRUE);
        ui->Deconnect->setEnabled(FALSE);

        ui->Affichage->setText("Lecteur déconnecté");
        ui->Affichage->update();
    }
}




void MainWindow::tag_hat(){
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON+LED_YELLOW_ON+LED_RED_ON+LED_GREEN_ON);
    DELAYS_MS(100);
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON);
}


void MainWindow::on_Quitter_clicked()
{
    int16_t status = MI_OK;
    RF_Power_Control(&MonLecteur, FALSE, 0);
    status = LEDBuzzer(&MonLecteur, LED_OFF);
    status = CloseCOM(&MonLecteur);
    qApp->quit();
}

QString MainWindow::convertirIntToQstring(int monEntier){
    return QString::number(monEntier);
}

uint8_t* MainWindow::convertirQstringToChar(QString DataText) {
    char DataIn[240];
    sprintf(DataIn, DataText.toUtf8().data(), 240);
    qDebug() << (uint8_t*)DataIn;
    return (uint8_t*)DataIn;
}

void MainWindow::on_connectCarte_clicked()
{
     status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);

     if (status == 0){
         ui->Saisie->setEnabled(TRUE);
         ui->incrementButton->setEnabled(TRUE);
         ui->decrementButton->setEnabled(TRUE);

         uint8_t dataPrenom[16];
         status = Mf_Classic_Read_Block(&MonLecteur, TRUE, 9, dataPrenom, AuthKeyA, 2);

         uint8_t dataNom[16];
         status = Mf_Classic_Read_Block(&MonLecteur, TRUE, 10, dataNom, AuthKeyA, 2);


         ui->nom->setText((char*)dataNom);
         ui->nom->update();

         ui->prenom->setText((char*)dataPrenom);
         ui->prenom->update();

         ui->Affichage->setText("Carte détectée");
         ui->Affichage->update();

        this->actualiserIncrement();

        this->tag_hat();
     } else {
         ui->nom->setText("Erreur lecture carte");
         ui->nom->update();

         ui->prenom->setText("Erreur lecture carte");
         ui->prenom->update();

         ui->nbUnite->setPlainText("Erreur lecture carte");
         ui->nbUnite->update();

         ui->Affichage->setText("Erreur lecture carte");
         ui->Affichage->update();

         ui->Saisie->setEnabled(FALSE);
         ui->incrementButton->setEnabled(FALSE);
         ui->decrementButton->setEnabled(FALSE);
     }
}

void MainWindow::on_Saisie_clicked()
{

    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);

    if (status == 0) {
        QString nomText = ui->nom->toPlainText();
        QString prenomText = ui->prenom->toPlainText();

        char DataInPrenom[16];
        sprintf(DataInPrenom, prenomText.toUtf8().data(), 16);
        auto dataPrenom = (uint8_t*)DataInPrenom;

        char DataInNom[16];
        sprintf(DataInNom, nomText.toUtf8().data(), 16);
        auto dataNom = (uint8_t*)DataInNom;

        status = Mf_Classic_Write_Block(&MonLecteur, TRUE, 9, dataPrenom, AuthKeyB, 2);
        status = Mf_Classic_Write_Block(&MonLecteur, TRUE, 10, dataNom, AuthKeyB, 2);

        this->tag_hat();
    } else {
        ui->Affichage->setText("Erreur lecture carte");
        ui->Affichage->update();
    }




}



void MainWindow::on_incrementButton_clicked()
{
    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);
    if (status == 0) {
        auto dataCompteur = ui->increment->value();
        status = Mf_Classic_Increment_Value(&MonLecteur, TRUE, 14, dataCompteur, 13, AuthKeyB, 3);
        status= Mf_Classic_Restore_Value(&MonLecteur, TRUE, 13, 14, AuthKeyA, 3);

        this->actualiserIncrement();

        this->tag_hat();
    } else {
        ui->Affichage->setText("Erreur lecture carte");
        ui->Affichage->update();
    }


}

void MainWindow::on_decrementButton_clicked()
{
    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);
    if (status == 0) {
        auto dataCompteur = ui->decrement->value();
        status = Mf_Classic_Decrement_Value(&MonLecteur, TRUE, 14, dataCompteur, 13, AuthKeyA, 3);
        status= Mf_Classic_Restore_Value(&MonLecteur, TRUE, 13, 14, AuthKeyA, 3);

        this->actualiserIncrement();

        this->tag_hat();
    } else {
        ui->Affichage->setText("Erreur lecture carte");
        ui->Affichage->update();
    }
}

void MainWindow::actualiserIncrement(){
    ui->nbUnite->setPlainText(this->convertirIntToQstring(this->getNbUniteRestante()));
    ui->nbUnite->update();
}

int MainWindow::getNbUniteRestante(){
    uint32_t dataCompteur = 0;
    status = Mf_Classic_Read_Value(&MonLecteur, TRUE, 14, &dataCompteur, AuthKeyA, 3);

    return dataCompteur;
}


