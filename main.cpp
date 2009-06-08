#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("perlanegra");
    a.setApplicationName("pares");
    MainWindow w;
    w.show();
    return a.exec();
}
