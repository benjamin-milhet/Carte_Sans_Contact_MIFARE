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
    qDebug() << "OpenCOM" << status;

    status = Version(&MonLecteur);
    ui->Affichage->setText(MonLecteur.version);
    ui->Affichage->update();

    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON+LED_YELLOW_ON+LED_RED_ON+LED_GREEN_ON);
    DELAYS_MS(100);
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON);

    char s_buffer[64];


    MonLecteur.Type = ReaderCDC;
    MonLecteur.device = 0;

     switch(MonLecteur.Type)
     {
         case ReaderTCP:
              qDebug() << (s_buffer, "IP : %s", MonLecteur.IPReader);
         break;
         case ReaderCDC:
              qDebug() << (s_buffer, "COM%d", MonLecteur.device);
         break;

     }

    status = Version(&MonLecteur);
    if (status == MI_OK){
         qDebug() << ("Reader firwmare is %s\n", MonLecteur.version);
         qDebug() << ("Reader serial is %02X%02X%02X%02X\n", MonLecteur.serial[0], MonLecteur.serial[1], MonLecteur.serial[2], MonLecteur.serial[3]);
         qDebug() << ("Reader stack is %s\n", MonLecteur.stack);
    }

    status = LEDBuzzer(&MonLecteur, LED_YELLOW_ON);
    if (status != MI_OK){
        printf("LED [FAILED]\n");
    }

    // RF field ON
    RF_Power_Control(&MonLecteur, TRUE, 0);
}


void MainWindow::on_Saisie_clicked()
{

    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);

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


}

void MainWindow::tag_hat(){
    // Halt the tag
    status = ISO14443_3_A_Halt(&MonLecteur);
    if (status != MI_OK){
        qDebug() << ("Failed to halt the tag\n");
        this->close();
    }


    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON+LED_YELLOW_ON+LED_RED_ON+LED_GREEN_ON);
    DELAYS_MS(1);
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON);
    //this->init();
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

     uint8_t dataPrenom[16];
     status = Mf_Classic_Read_Block(&MonLecteur, TRUE, 9, dataPrenom, AuthKeyA, 2);

     uint8_t dataNom[16];
     status = Mf_Classic_Read_Block(&MonLecteur, TRUE, 10, dataNom, AuthKeyA, 2);


     ui->nom->setText((char*)dataNom);
     ui->nom->update();

     ui->prenom->setText((char*)dataPrenom);
     ui->prenom->update();

    this->actualiserIncrement();

}



void MainWindow::on_incrementButton_clicked()
{
    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);
    auto dataCompteur = ui->increment->value();
    status = Mf_Classic_Increment_Value(&MonLecteur, TRUE, 14, dataCompteur, 14, AuthKeyB, 3);

    this->actualiserIncrement();

}

void MainWindow::on_decrementButton_clicked()
{
    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);
    auto dataCompteur = ui->decrement->value();
    status = Mf_Classic_Decrement_Value(&MonLecteur, TRUE, 14, dataCompteur, 14, AuthKeyB, 3);

    this->actualiserIncrement();
}

void MainWindow::actualiserIncrement(){
    ui->nbUnite->setPlainText(this->convertirIntToQstring(this->getNbUniteRestante()));
    ui->nbUnite->update();
}

int MainWindow::getNbUniteRestante(){
    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);

    uint32_t dataCompteur = 0;
    status = Mf_Classic_Read_Value(&MonLecteur, TRUE, 14, &dataCompteur, AuthKeyA, 3);

    return dataCompteur;
}
