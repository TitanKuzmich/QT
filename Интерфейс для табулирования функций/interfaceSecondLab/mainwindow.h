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

protected:
    void header();          //вывод шапки
    void content();         //вывод содержимого таблицы
    void footer();          //вывод нижней части таблицы
    void calc();            //расчет функций

protected:
    double A;                 //конец интервала
    double B;                 //конец интервала
    int    N;                 //число интервалов
    double h;                 //шаг
    double X;               //аргумент
    double F;               //функция F(x) = sqrt(X^2 + 4)
    double G;               //функция G(x) = (X+5)^3 / (1+sin^2(x))
    int i;                  //параметр цикла
    QString whiteSpace;     //пробелы
    QString arg;            //аргумент
    QString F1;             //первая функция
    QString G1;             //вторая функция

private:
    Ui::MainWindow *ui;

private slots:
    void tabulation();      //табуляция расчетов
};
#endif // MAINWINDOW_H
