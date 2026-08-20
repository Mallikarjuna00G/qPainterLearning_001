#include "canvaswidget.hpp"
#include <QPainter>
#include <QDebug>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{

}

CanvasWidget::~CanvasWidget() = default;

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    // Initialize painter for this widget
    QPainter painter(this);

    // Query active status (prints to debug output in Qt Creator)
    qDebug() << "Is painter active?:" << painter.isActive();

    // Draw a simple line from top-left (0, 0) to bottom-right (200, 200).
    painter.drawLine(0, 0, 200, 200);
}
