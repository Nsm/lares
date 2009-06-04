#ifndef ARESDOWNLOADWIDGETDELEGATE_H
#define ARESDOWNLOADWIDGETDELEGATE_H

#include <QItemDelegate>
#include <QApplication>
#include "aresdownloadwidgetitem.h"

class AresDownloadWidgetDelegate : public QItemDelegate
{
public:
    AresDownloadWidgetDelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index ) const;
};

#endif // ARESDOWNLOADWIDGETDELEGATE_H
