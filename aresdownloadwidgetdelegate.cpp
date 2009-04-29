#include "aresdownloadwidgetdelegate.h"

AresDownloadWidgetDelegate::AresDownloadWidgetDelegate()
{
}

void AresDownloadWidgetDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index ) const
{
    if (index.column() != 3) {
        QItemDelegate::paint(painter, option, index);
        return;
    }

    // Set up a QStyleOptionProgressBar to precisely mimic the
    // environment of a progress bar.
    QStyleOptionProgressBar progressBarOption;
    progressBarOption.state = QStyle::State_Enabled;
    progressBarOption.direction = QApplication::layoutDirection();
    progressBarOption.rect = option.rect;
    progressBarOption.fontMetrics = QApplication::fontMetrics();
    progressBarOption.minimum = 0;
    progressBarOption.maximum = 100;
    progressBarOption.textAlignment = Qt::AlignCenter;
    progressBarOption.textVisible = true;

    // Set the progress and text values of the style option.
    QVariant value = index.data(Qt::DisplayRole);
    int progress = value.toInt();
    progressBarOption.progress = progress < 0 ? 0 : progress;
    progressBarOption.text = QString().sprintf("%d%%", progressBarOption.progress);

    // Draw the progress bar onto the view.
    QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
}
