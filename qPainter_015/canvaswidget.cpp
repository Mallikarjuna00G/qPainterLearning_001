#include "canvaswidget.hpp"
#include <QPainter>
#include <QPen>
#include <QList>
#include <QPolygonF>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // --- 1. PEN CAPS (Endings of open lines)
    // We will draw 3 thick, horizontal lines to compare caps.
    // We also draw thin gray reference lines exactly at the start/end
    // coordinates so we can see how the cap extends PAST the geometric point.
    QPen capPen(Qt::blue);
    capPen.setWidth(20);  // Thick pen to make the CAP obvious

    // Qt::FlatCap: Stops exactly at the end point (deafult)
    capPen.setCapStyle(Qt::FlatCap);
    painter.setPen(capPen);
    painter.drawLine(100, 50, 400, 50);

    // Qt::SquareCap: Extends past the end point by half the line width
    capPen.setCapStyle(Qt::SquareCap);
    painter.setPen(capPen);
    painter.drawLine(100, 100, 400, 100);

    // Qt::RoundCap: Extends past the end point with a semi-circle
    capPen.setCapStyle(Qt::RoundCap);
    painter.setPen(capPen);
    painter.drawLine(100, 150, 400, 150);

    // Draw reference lines to show geometric start/end boundries
    painter.setPen(QPen(Qt::lightGray, 1, Qt::DashLine));
    painter.drawLine(100, 30, 100, 170);
    painter.drawLine(400, 30, 400, 170);

    // --- 2. PEN JOINS (Corners of connected lines) ---
    // We will draw 3 identical polylines side-by-side to compare corner styles

    QPolygonF cornerShape;
    cornerShape << QPointF(0, 50) << QPointF(50, 0) << QPointF(100, 50);  // Sharp V-shape

    QPen joinPen(Qt::darkGreen);
    joinPen.setWidth(20);

    painter.save();  // Isolate transform state
    painter.translate(100, 250);  // Move down to join section

    // Qt::MiterJoin: Sharp extended corner (default)
    joinPen.setJoinStyle(Qt::MiterJoin);
    painter.setPen(joinPen);
    painter.drawPolyline(cornerShape);

    painter.translate(150, 0);  // Shift right for next shape

    // Qt::BevelJoin: Flat cut across the corner
    joinPen.setJoinStyle(Qt::BevelJoin);
    painter.setPen(joinPen);
    painter.drawPolyline(cornerShape);

    painter.translate(150, 0);  // Shift right for next shape

    // Qt::RoundJoin: Smooth rounded corner
    joinPen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(joinPen);
    painter.drawPolyline(cornerShape);

    painter.restore();  // Reset translation

    // --- 3. CUSTOM DASH PATTERNS ---
    // Instead of built-in Qt::DashLine, we can define exact pixel ratios.
    // The pattern is an array of qreal values: [Solid, Empty, Solid, Empty, ...]
    // The numbers represent multiples of the Pen width!
    QPen dashPen(Qt::red);
    dashPen.setWidth(4);

    // Define custom pattern:
    // 4 units solid, 2 units empty, 1 unit sold, 2 units empty
    QList<qreal> customPattern {4.0, 2.0, 1.0, 2.0};

    dashPen.setDashPattern(customPattern);

    painter.setPen(dashPen);
    painter.drawLine(100, 380, 500, 380);
}