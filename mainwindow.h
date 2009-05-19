#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QLabel>
#include <QTabWidget>
#include <QHash>
#include <QDir>
#include <QMessageBox>
#include <Phonon>
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
    Phonon::MediaObject * mediaPreview;
    Phonon::SeekSlider *seekSlider;
private slots:
    void on_tbPreviewStop_clicked();
    void on_tbPreviewPause_clicked();
    void on_tbPreviewPlay_clicked();
    void on_pbStopSearch_clicked();
    void on_pbSearch_clicked();
    void on_pbConnect_clicked();
    void connectionStatusChanged(AresConnection::Status newStatus);
    void itemFinded(AresItem * item, int searchId);
    void currentSearchTabChanged(int tabId);
public slots:
    void startDownload(AresDownloadRequest * download);
    void downloadStarted(AresDownload * download);
    void closeSearchTab(int tabId);
    void previewDownload(int downloadId);
};

#endif // MAINWINDOW_H
