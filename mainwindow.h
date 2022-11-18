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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    uint8_t* convertirQstringToChar(QString DataText);
    QString convertirIntToQstring(int monEntier);
    int card_read(uint8_t sect_count);
    void tag_hat();
    void init();
    void close();






private slots:
    void on_Connect_clicked();

    void on_Saisie_clicked();

    void on_Quitter_clicked();

    void on_connectCarte_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
