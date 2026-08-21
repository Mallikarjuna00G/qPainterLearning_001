#include "canvaswidget.hpp"
#include <QPainter>
#include <QRectF>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // --- 1. Fill a Rectangle ---
    // fillRect() is highly optimized. It doesn't even use the current
    // QPen or QBrush. It just blasts the color straight into the
    // bounding box.
    QRectF solidBlock(50.5, 50.5, 300.0, 200.0);
    painter.fillRect(solidBlock, Qt::darkCyan);

    // --- 2. Erase a Rectangle ---
    // eraseRect() punches a hole right through whatever is already
    // drawn, replacing the pixels with the widget's default
    // background color.
    QRectF holeBlock(100.5, 100.5, 200.0, 100.0);
    painter.eraseRect(holeBlock);
}