#ifndef ARESSEARCHWIDGET_H
#define ARESSEARCHWIDGET_H

#include <QtGui/QWidget>
#include <QTabWidget>
#include <QTreeWidget>
#include "aresitem.h"

namespace Ui {
    class AresSearchWidget;
}

class AresSearchWidget : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(AresSearchWidget)
public:
    explicit AresSearchWidget(QWidget *parent = 0);
    virtual ~AresSearchWidget();
    void addItem(AresItem * item, int searchId);
    void addSearch(int searchId,QString searchTitle);
protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::AresSearchWidget *m_ui;
    QTabWidget *tabSearch;
};

#endif // ARESSEARCHWIDGET_H
