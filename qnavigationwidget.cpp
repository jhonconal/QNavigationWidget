#include "qnavigationwidget.h"
#include <QPainter>
#include <QDebug>

QNavigationWidget::QNavigationWidget(QWidget *parent) : QWidget(parent)
{
    backgroundColor = "#E4E4E4";
    selectedColor = "#2CA7F8";
    rowHeight = 40;

    setMouseTracking(true);
    setFixedWidth(200);
}

QNavigationWidget::~QNavigationWidget()
{
}

void QNavigationWidget::addItem(const QString &title)
{
    listItems << title;

    repaint();
}

void QNavigationWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Draw background color.
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(backgroundColor));
    painter.drawRect(rect());

    // Draw Items
    int count = 0;
    for (const QString &str : listItems) {
        QPainterPath itemPath;
        itemPath.addRect(QRect(0, count * rowHeight, width(), rowHeight));
        
        bool isSelect = selectItems.contains(str);
        
        if (isSelect) {
            painter.setPen("#FFFFFF");
            painter.fillPath(itemPath, QColor(selectedColor));
        }else {
            painter.setPen("#202020");
            painter.fillPath(itemPath, QColor(backgroundColor));
        }
        painter.drawText(QRect(0, count * rowHeight, width(), rowHeight), Qt::AlignCenter, str);

        ++count;
    }
}

void QNavigationWidget::mouseMoveEvent(QMouseEvent *e)
{
    
}

void QNavigationWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->y() / rowHeight < listItems.count()) {
        const int currentIndex = e->y() / rowHeight;

        selectItems.clear();
        selectItems << listItems.at(currentIndex);

        repaint();
    }
}

void QNavigationWidget::mouseReleaseEvent(QMouseEvent *e)
{
    
}
