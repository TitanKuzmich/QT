/******************************************************
 *	                                                  *
 *	      Информатика и Вычислительная техника        *
 *	                                                  *
 ******************************************************
 *	Progect type: Win32 Console Application1          *
 *	Progect name: InterfaceSecondLab                  *
 *	File name:    InterfaceSecondLab.cpp              *
 *	language:     cpp, Qt               	          *
 *	Programmers:  M3O-107Б-18                         *
 *	              Кривонос Александр Александрович    *
 *                                                    *
 *	Modified by:                                      *
 *	Created:      20.06.2020 Last revision:25.06.2020 *
 ******************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->calc, SIGNAL(clicked()),this,SLOT(tabulation()));                                           //соединяем сигнал со слотом
    ui->upperBound->setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*|0)(\\.)[0-9]{8}"), this));     //валидатор для верхней границы
    ui->lowerBound->setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*|0)(\\.)[0-9]{8}"), this));     //валидатор для нижней границы
    ui->numOfIntervals->setValidator(new QIntValidator());                                                  //валидатор для числа интервалов
}

//деструктор
MainWindow::~MainWindow()
{
    delete ui;
}

/*Вывод шапки*/
void MainWindow::header(){
    ui->tableOutput->insertPlainText("┌────────────┬────────────────┬─────────────┐\n"
                                     "│     X      │      F(x)      │     G(x)    │\n"
                                     "├────────────┼────────────────┼─────────────┤\n");
    ui->tableOutput->moveCursor (QTextCursor::End);
}

/*Вывод содержимого расчетов*/
void MainWindow::content(){
    ui->tableOutput->insertPlainText("│");
    ui->tableOutput->moveCursor (QTextCursor::End);

    ui->tableOutput->insertPlainText(whiteSpace.fill(' ', 4));//вывод значения аргумента
    ui->tableOutput->moveCursor (QTextCursor::End);
    ui->tableOutput->insertPlainText(arg);
    ui->tableOutput->insertPlainText(whiteSpace.fill(' ', 8-arg.length()));//вывод значения аргумента


    ui->tableOutput->moveCursor (QTextCursor::End);
    ui->tableOutput->insertPlainText("│");
    ui->tableOutput->moveCursor (QTextCursor::End);

    ui->tableOutput->insertPlainText(whiteSpace.fill(' ', 6));//вывод значения функции F(X)
    ui->tableOutput->moveCursor (QTextCursor::End);
    ui->tableOutput->insertPlainText(F1);
    ui->tableOutput->insertPlainText(whiteSpace.fill(' ', 10-F1.length()));//вывод значения функции F(X)


    ui->tableOutput->moveCursor (QTextCursor::End);
    ui->tableOutput->insertPlainText("│");
    ui->tableOutput->moveCursor (QTextCursor::End);

    ui->tableOutput->insertPlainText(whiteSpace.fill(' ', 4));//вывод значения функции G(X)
    ui->tableOutput->moveCursor (QTextCursor::End);
    ui->tableOutput->insertPlainText(G1);
    ui->tableOutput->insertPlainText(whiteSpace.fill(' ', 9-G1.length()));//вывод значения функции G(X)

    ui->tableOutput->moveCursor (QTextCursor::End);
    ui->tableOutput->insertPlainText("│\n");
    ui->tableOutput->moveCursor (QTextCursor::End);
}

/*Вывод нижней части таблицы*/
void MainWindow::footer(){
    ui->tableOutput->insertPlainText("└────────────┴────────────────┴─────────────┘\n");
    ui->tableOutput->moveCursor (QTextCursor::End);
}

/*Расчет функций*/
void MainWindow::calc(){
    F = sqrt(X*X + 4);                                   //вычисление функции F(X)
    G = ((X + 5)*(X + 5)*(X + 5)) / (1 + sin(X)*sin(X)); //вычисление функции G(X)
    //приведение к типу строк
    arg = QString::number(X, 10, 2);
    F1 = QString::number(F, 10, 2);
    G1 = QString::number(G, 10, 2);
}

void MainWindow::tabulation()
{
    A = ui->upperBound->text().toDouble();             //ввод А
    B = ui->lowerBound->text().toDouble();             //ввод В
    if (B < A)                                          //входной контроль
    {
        QMessageBox::critical(this, "Ошибка", "Верхняя граница должна быть больше нижней!");
        return;
    }

    ui->tableOutput->clear();       //очищаем полевывода таблицы

    if (A == B)
    {
        X = A ;                     //вычисление аргумента
        calc();                     //вычиление функций

        /*Вывод верхней части таблицы*/
        header();

        /*Вывод содержимого расчетов*/
        content();

        /*Вывод нижней части таблицы*/
        footer();

        return;
    }

    else
    {
        N = ui->numOfIntervals->text().toInt(); //считываем количество интервалов

        if (N <= 0)                             //входной контроль
        {
            QMessageBox::critical(this, "Ошибка", "Введите число интервалов (больше нуля)!");
            return;
        }//if

        ui->tableOutput->clear();    //очищаем поле вывода таблицы
        h = (B - A) / N;             //вычисление шага

        /*Вывод верхней части таблицы*/
        header();

        for (i = 0; i <= N; i++)
        {
            X = A + i * h;        //вычисление аргумента
            calc();               //вычиление функций

            /*Вывод содержимого расчетов*/
            content();

            /*Дорисовка ячеек таблицы*/
            if (i < N)
            {
               ui->tableOutput->insertPlainText("├────────────┼────────────────┼─────────────┤\n");
               ui->tableOutput->moveCursor (QTextCursor::End);
            }
        }//for i;

        /*Вывод нижней части таблицы*/
        footer();
    }//else

    return;
}
