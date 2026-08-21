#include "canvaswidget.hpp"
#include <QPainter>
#include <QBrush>
#include <QPen>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(Qt::darkMagenta, 3));

    // We will set a cyan brush so you can see exactly how Polygons
    // handle interior filling versus polylines
    painter.setBrush(QBrush(Qt::cyan));

    // 1. PolyLine (An open path)
    // Think of it as a stock market graph. it does not connect the last point back
    // to the first. Zero fill.
    QPolygonF polylinePoints {
        QPointF(20.0, 100.0),
        QPointF(50.0, 20.0),
        QPointF(80.0, 100.0),
        QPointF(110.0, 50.0),
        QPointF(140.0, 100.0)
    };
    painter.drawPolyline(polylinePoints);

    // 2. Polygon (A closed path)
    // This is the exact same "M" shape as above, but drawn as a polygon.
    // Notice the two things:
    // a. It automatically draws a line from the last point back to the first.
    // b. It perfectly contains the cyan color fill.
    QPolygonF polygonPoints {
        QPointF(180.0, 100.0),
        QPointF(210.0, 20.0),
        QPointF(240.0, 100.0),
        QPointF(270.0, 50.0),
        QPointF(300.0, 100.0)
    };
    painter.drawPolygon(polygonPoints);

    // 3. Convex polygon (A highly optimized closed path)
    // We draw a perfect hexagon here (which has no dents, so it is safe to use
    // the convex optimizer)
    QPolygonF convexPoints {
        QPointF(370.0, 20.0),
        QPointF(420.0, 20.0),
        QPointF(450.0, 60.0),
        QPointF(420.0, 100.0),
        QPointF(370.0, 100.0),
        QPointF(340.0, 60.0)
    };
    painter.drawConvexPolygon(convexPoints);
}