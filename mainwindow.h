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
    void on_pushButton_clicked();
    void connectionStatusChanged(AresConnection::Status newStatus);
};

#endif // MAINWINDOW_H
