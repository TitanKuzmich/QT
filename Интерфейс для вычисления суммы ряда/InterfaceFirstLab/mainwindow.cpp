/******************************************************
 *	                                                  *
 *	      Информатика и Вычислительная техника        *
 *	                                                  *
 ******************************************************
 *	Progect type: Win32 Console Application1          *
 *	Progect name: InterfaceFirstLab                   *
 *	File name:    InterfaceFirstLab.cpp               *
 *	language:     cpp, Qt               	          *
 *	Programmers:  M3O-107Б-18                         *
 *	              Кривонос Александр Александрович    *
 *                                                    *
 *	Modified by:                                      *
 *	Created:      20.06.2020 Last revision:25.06.2020 *
 ******************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QString>

//функция инициализации
void MainWindow::init(){
    E = 2.71828;                    //Неперово число
    N = 1;                          //Номер слагаемого
    Znak = -1;                      //Знак слагаемого
    Sum = 0;                        //Текущая сумма
    TSum = 1 / E;                   //Точная сумма
    Diff = std::abs(TSum - Sum);    //Разница
    NFact = 1;                      //N!
}

//конструктор
MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/res/img/rowSum.png");            //задаем картинку
    int w = ui->image->width();                     //ширина
    int h = ui->image->height();                    //высота

    ui->image->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    connect(ui->calc, SIGNAL(clicked()),this,SLOT(valueOfRow()));       //соединяем сигнал со слотом
    ui->accuracyEdit->setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*|0)(\\.)[0-9]{8}"), this));       //задаем валидатор

    init();                                         //Инициализация переменных
}

//деструктор
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::valueOfRow()
{
    ui->accuracyEdit->setLocale(QLocale::c());      //задаем русский язык

    eps = ui->accuracyEdit->text().toDouble();      //считываем eps

    if(eps <= 0.0 || ui->accuracyEdit->text().isEmpty()){
        ui->statusbar->showMessage("Введите корректную точность (больше нуля)");
        return;
    }
    while (Diff > eps)
    {
        N = N + 1;                      //количество слагаемых увеличиваем на 1
        Znak = -Znak;                   //знак меняем на противоположный
        NFact = N * NFact;              //вычисляет N! факториал
        Slag = Znak / NFact;            //вычисляет слагаемое

        Sum = Sum + Slag;               //вычисляет сумму(предыдущая сумма плюс слагаемое)
        Diff = std::abs(TSum - Sum);    //разница между точной суммой и текущей
    } //while

    ui->statusbar->showMessage("Все ок)");  //сообщение в статусбар

    //вывод результата
    ui->exactV->setText(QString::number(TSum));
    ui->numOfTermsV->setText(QString::number(N));
    ui->valueCurrentV->setText(QString::number(Sum));
    ui->differenceV->setText(QString::number(Diff));

   init();                                  //задание начальных значений переменным

}
