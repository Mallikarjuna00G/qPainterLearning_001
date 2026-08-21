#include "canvaswidget.hpp"
#include <QPainter>
#include <QPen>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{}

CanvasWidget::~CanvasWidget() = default;

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Set a nice thick pen so we can see the curves
    painter.setPen(QPen(Qt::darkMagenta, 4));

    // 1. Circle (A perfect ellipse)
    // Qt already natively supports a center/radius overload for full ellipses!
    // We don't need a helper function here.
    QPointF centerEllipse(70.5, 70.5);
    qreal radiusEllipse = 50.0;
    painter.drawEllipse(centerEllipse, radiusEllipse, radiusEllipse);

    // We manually calculate the bounding box here just for our dashed-line visualizer at the bottom
    QRectF rectEllipse(centerEllipse.x() - radiusEllipse, centerEllipse.y() - radiusEllipse, radiusEllipse * 2.0, radiusEllipse * 2.0);

    // Angles for partial curves:
    int startAngle {30};  // Start at 30 degrees counter-clockwise from 3 o-clock
    int spanAngle {120};  // Sweep for 120 degrees

    // 2. Arc (Just the outer stroked curve)
    QRectF rectArc {drawArcIntuitive(painter, QPointF(250.0, 75.0), 50, startAngle, spanAngle)};

    // 3. Pie (Curve connected back to the center point, like a pizza slice)
    QRectF rectPie {drawPieIntuitive(painter, QPointF(100.0, 200.0), 50, startAngle, spanAngle)};

    // 4. Chord (Curve with a straight line connecting its two endpoints)
    QRectF rectChord {drawChordIntuitive(painter, QPointF(250.0, 200.0), 50, startAngle, spanAngle)};

    // --- Visualization helper ---
    // Let's draw the bounding boxes lightly so you can visually see
    // exactly how the bounding rectangles constrain the curves!
    painter.setPen(QPen(Qt::lightGray, 1, Qt::DashLine));
    painter.drawRect(rectEllipse);
    painter.drawRect(rectArc);
    painter.drawRect(rectPie);
    painter.drawRect(rectChord);
}