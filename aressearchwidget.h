#ifndef ARESSEARCHWIDGET_H
#define ARESSEARCHWIDGET_H

#include <QtGui/QWidget>
#include <QTabWidget>
#include <QTreeWidget>
#include <QHash>
#include "aresitem.h"
#include "aressearchwidgetitem.h"

namespace Ui {
    class AresSearchWidget;
}

class AresSearchWidget : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(AresSearchWidget)
public:
    explicit AresSearchWidget(QWidget *parent = 0);
    virtual ~AresSearchWidget();
    void clear();
protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::AresSearchWidget *m_ui;
    QHash<QString, AresSearchWidgetItem *> itemsHash;

private slots:
    void on_twSearch_itemDoubleClicked(QTreeWidgetItem* item, int column);
signals:
    void downloadRequested(AresDownloadRequest * download);

public slots:
    void addItem(AresItem * item);

};

#endif // ARESSEARCHWIDGET_H
