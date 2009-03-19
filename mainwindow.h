#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QLabel>
#include "aresconnection.h"

namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindowClass *ui;
    AresConnection *connection;
    QLabel * statusMessage;
private slots:
    void on_pbConnect_clicked();
    void on_leSearch_returnPressed();
    void connectionStatusChanged(AresConnection::Status newStatus);
    void itemFinded(AresItem * item, int searchId);
};

#endif // MAINWINDOW_H
