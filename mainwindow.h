#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QLabel>
#include <QTabWidget>
#include <QHash>
#include "aresconnection.h"
#include "aressearchwidget.h"
#include "aresdownloadwidget.h"
#include "aresdownloadrequest.h"
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
    QTabWidget * tabSearchResult;
    QHash<int,AresSearchWidget *> searchWidgets;
    AresDownloadWidget * downloadWidget;
private slots:
    void on_pbConnect_clicked();
    void on_leSearch_returnPressed();
    void connectionStatusChanged(AresConnection::Status newStatus);
    void itemFinded(AresItem * item, int searchId);
public slots:
    void startDownload(AresDownloadRequest * download);
    void downloadStarted(AresDownload * download);
};

#endif // MAINWINDOW_H
