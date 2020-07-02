#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;               //экземпляр главного окна
    w.show();                   //функция показа главного окна

    return a.exec();
}
