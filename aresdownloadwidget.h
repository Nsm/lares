#ifndef ARESDOWNLOADWIDGET_H
#define ARESDOWNLOADWIDGET_H

#include <QtGui/QWidget>
#include "aresdownload.h"
#include <QTreeWidgetItem>
#include <QHash>
#include "aresdownloadwidgetdelegate.h"

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
    QHash<int, QTreeWidgetItem *> itemsHash;

public slots:
    void addDownload(AresDownload *download);
    void updateDownload(AresDownload *download);
};

#endif // ARESDOWNLOADWIDGET_H
