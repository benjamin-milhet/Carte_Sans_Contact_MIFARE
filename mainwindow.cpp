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

void MainWindow::init() {
    qDebug() << ("Attente carte !\n");
    while(ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len));
    if (status != MI_OK){
        qDebug() << ("No available tag in RF field\n");
        this->close();
    }

    qDebug() << ("Tag found: UID=");
    for (i = 0; i < uid_len; i++)
        qDebug() << ("%02X", uid[i]);
    qDebug() << (" ATQ=%02X%02X SAK=%02X\n", atq[1], atq[0], sak[0]);


    /*if ((atq[1] != 0x00) || ((atq[0] != 0x02) && (atq[0] != 0x04) && (atq[0] != 0x18))){
        printf("This is not a Mifare classic tag\n");
        goto tag_halt;
    }*/

    if ((sak[0] & 0x1F) == 0x08){
        // Mifare classic 1k : 16 sectors, 3+1 blocks in each sector
        qDebug() << ("Tag appears to be a Mifare classic 1k\n");
        sect_count = 16;
    } else if ((sak[0] & 0x1F) == 0x18){
        // Mifare classic 4k : 40 sectors, 3+1 blocks in 32-first sectors, 15+1 blocks in the 8-last sectors
        qDebug() << ("Tag appears to be a Mifare classic 4k\n");
        sect_count = 40;
    }


    status = card_read(sect_count);
    this->tag_hat();

}


void MainWindow::on_Saisie_clicked()
{

    QString Text = ui->fenetre_saisi->toPlainText();
    qDebug() << "Text : " << Text;
    status = OpenCOM(&MonLecteur);

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

char MainWindow::convertirQstringToChar() {
    char DataIn[16];
    char res = sprintf(DataIn, ui->fenetre_saisi->toPlainText().toUtf8().data(), 16);

    return res;
}

QString MainWindow::convertirIntToQstring(int monEntier){
    return QString::number(monEntier);
}

int MainWindow::card_read(uint8_t sect_count)
{

    uint8_t data[240] = {0};
    clock_t t0, t1;
    uint8_t bloc_count, bloc, sect;
    uint8_t offset;
    int16_t status = 0;
    uint8_t atq[2];
    uint8_t sak[1];
    uint8_t uid[12];
    uint16_t uid_len = 12;

    if (bench){
        qDebug() << ("Reading %d sectors...\n", sect_count);
        t0 = clock();
    }
    bloc = 0;
    QString res = "";
    for (sect = 0; sect < sect_count; sect++){
        if (!bench)
        qDebug() << ("Reading sector %02d : ", sect);


        memset(data, 0x00, 240);
        status = Mf_Classic_Read_Sector(&MonLecteur, TRUE, 2, data, AuthKeyA, 2);
        res += (char*)data;
        /*if (status != MI_OK){
            if (bench)
                qDebug() << ("Read sector %02d ", sect);
            qDebug() << ("[Failed]\n");
            qDebug() << ("  %s (%d)\n", GetErrorMessage(status), status);
            status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);
            if (status != MI_OK){
                 qDebug() << ("No available tag in RF field\n");
            }
        }
        else{
            if (!bench){
                qDebug() << ("[OK]\n");
                // Display sector's data
                if (sect < 32)
                    bloc_count = 3;
                else
                    bloc_count = 15;
                for (bloc = 0; bloc < bloc_count; bloc++){
                    qDebug() << ("%02d : ", bloc);
                    // Each blocks is 16-bytes wide
                    for (offset = 0; offset < 16; offset++){
                        res += convertirIntToQstring(("%02X ", data[16 * bloc + offset]));
                    }
                    for (offset = 0; offset < 16; offset++){
                        if (data[16 * bloc + offset] >= ' '){
                            res += convertirIntToQstring(("%c", data[16 * bloc + offset]));
                        } else
                            res += (".");

                    }
                    res += ("\n");
                }
            }
        }*/
    }
    ui->fenetre_saisi->setText(res);
    ui->fenetre_saisi->update();


    qDebug() << res;

    if (bench){
        t1 = clock();
        qDebug() << ("Time elapsed: %ldms\n", (t1 - t0) / (CLOCKS_PER_SEC/1000));
    }
    return MI_OK;
}

void MainWindow::close() {
    RF_Power_Control(&MonLecteur, FALSE, 0);
    CloseCOM(&MonLecteur);
}

void MainWindow::on_connectCarte_clicked()
{
    this->init();
}
