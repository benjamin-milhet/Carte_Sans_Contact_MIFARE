#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); // Constructeur
    ~MainWindow(); // Destructeur
    uint8_t* convertirQstringToChar(QString DataText); // Convertir une QString en char
    QString convertirIntToQstring(int monEntier); // Convertir un int en QString
    void tag_hat(); // Fonction pout faire sonner le buzzer
    int getNbUniteRestante(); // Fonction pour récupérer le nombre d'unité restante
    void actualiserIncrement(); // Fonction pour actualiser le nombre d'unité restante
    void MelodyBuzzer(); // Fonction pour faire sonner le buzzer


private slots:
    void on_Connect_clicked(); // Fonction pour se connecter au lecteur RFID

    void on_Saisie_clicked(); // Fonction permettant d'actualiser les informations d'une carte MIFARE

    void on_Quitter_clicked(); // Fonction permettant de quitter l'application

    void on_connectCarte_clicked(); // Fonction permettant de récuperer les informations d'une carte MIFARE

    void on_incrementButton_clicked(); // Fonction permettant d'actualiser l'incrémentation

    void on_decrementButton_clicked(); // Fonction permettant d'actualiser la décrémentation

    void on_Deconnect_clicked(); // Fonction permettant de deconnecter le lecteur de carte
 
private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
