#include "canvaswidget.hpp"
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QBrush>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 300);
}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.translate(100, 150);

    // 1. Draw a sweeping cubic curve
    QPainterPath path;
    path.moveTo(0, 0);
    path.cubicTo(100, -200, 300, 200, 400, 0);

    painter.setPen(QPen(Qt::darkBlue, 3));
    painter.drawPath(path);

    // 2. Find the midpoint (t = 0.5)
    // t goes from 0.0 (start) to 1.0 (end)
    qreal t {0.5};
    const QPointF midPoint {path.pointAtPercent(t)};

    // 3. Find the Tangent Angle (in degrees)
    // This tells us the exact direction the curve is flowing at that point!
    const qreal angle {path.angleAtPercent(t)};

    // 4. Draw the Arrowhead!
    painter.save();
    // Move to the exact midpoint
    painter.translate(midPoint);

    // Qt's angleAtPercent returns mathematical angle (counter-clockwise from
    // 3 o'clock).
    // QPainter::rotate expects clockwise. We use a negative sign to flip it!
    painter.rotate(-angle);

    // Draw a simple triangle pointing to the right (since we already rotated
    // the canvas)
    QPainterPath arrowHead;
    arrowHead.moveTo(10, 0);  // Tip
    arrowHead.lineTo(-10, -8);  // Top Back
    arrowHead.lineTo(-5, 0);  // Inner notch
    arrowHead.lineTo(-10, 8);  // Bottom back
    arrowHead.closeSubpath();

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.drawPath(arrowHead);

    painter.restore();

    // Optional: Draw a small circle exactly on the midPoint to see where
    // the arrow is anchored.
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawEllipse(midPoint, 3, 3);
}