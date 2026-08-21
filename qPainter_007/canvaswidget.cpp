#include "canvaswidget.hpp"
#include <QPointF>
#include <QLineF>
#include <QRectF>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{}

CanvasWidget::~CanvasWidget() = default;

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Critical: Antialiasing is what physically allows the
    // screen to render sub-pixel math smoothly by blending opacities
    // on the edges!
    painter.setRenderHint(QPainter::Antialiasing, true);

    // --- 1. Sub-pixel precision Points & Lines ---
    drawALine(painter);
    // --- 2. Sub-pixel precision Rectangles ---
    drawARectangle(painter);
}

void drawALine(QPainter &painter) {
    // Notice how we use decimals. Using QPoint would lose our mathematical
    // precision.
    QPointF startPoint(50.75, 50.25);
    QPointF endPoint(250.33, 150.88);

    // QLineF takes two QPointF objects
    QLineF preciseLine(startPoint, endPoint);

    painter.setPen(QPen(Qt::blue, 3));

    // QPainter has an overload that specifically accepts a QLineF
    painter.drawLine(preciseLine);
}

void drawARectangle(QPainter &painter)
{
    QRectF preciseRect(50.5, 200.5, 100.25, 75.75);

    painter.setPen(QPen(Qt::red, 2));
    // QPainter has an overload that specifically accepts a QRectF
    painter.drawRect(preciseRect);
}
