#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }          //пространство имен
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);//конструктор
    ~MainWindow();                        //деструктор

private:
    Ui::MainWindow *ui;

private slots:
    void valueOfRow();            //расчет значения

protected:
    double eps;                   //Заданная точность
    double E;                     //Неперово число
    double TSum;                  //Точная сумма
    double Sum;                   //Текущая сумма
    double Diff;                  //Разница между точной суммой и текущей
    double Slag;                  //Слагаемое
    double NFact;                 //N!
    int N;                        //Номер слагаемого
    int Znak;                     //Знак слагаемого

    void init();

};
#endif // MAINWINDOW_H
