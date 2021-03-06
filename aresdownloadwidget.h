#ifndef ARESDOWNLOADWIDGET_H
#define ARESDOWNLOADWIDGET_H

#include <QtGui/QWidget>
#include "aresdownload.h"
#include <QTreeWidgetItem>
#include <QHash>
#include <QMenu>
#include "aresdownloadwidgetdelegate.h"
#include "aresdownloadwidgetitem.h"

namespace Ui {
    class AresDownloadWidget;
}

class AresDownloadWidget : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(AresDownloadWidget)
public:
    explicit AresDownloadWidget(QWidget *parent = 0);
    virtual ~AresDownloadWidget();
protected:
    virtual void changeEvent(QEvent *e);
private:
    Ui::AresDownloadWidget *m_ui;
    //hash que contiene todos los items relacionados con el identificador de la descarga asociada
    QHash<int, AresDownloadWidgetItem *> itemsHash;

public slots:
    void addDownload(AresDownload *download);
    void updateDownload(int downloadId);
    void removeDownload(int downloadId);
protected slots:
    void showContextMenu( const QPoint & pos );

void on_actionRemove_triggered();
    private slots:
    void on_actionFindSources_triggered();
    void on_actionPreview_triggered();
    void on_actionRemoveAll_triggered();
    void on_actionResume_triggered();
    void on_actionPause_triggered();
    void on_actionCancel_triggered();

signals:
    void downloadCancelled(int downloadId);
    void downloadPaused(int downloadId);
    void downloadResumed(int downloadId);
    void downloadRemoved(int downloadId);
    void downloadPreviewed(int downloadId);
    void sourcesFinded(int downloadId);

};

#endif // ARESDOWNLOADWIDGET_H
