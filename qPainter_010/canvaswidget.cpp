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

    // 1. Ellipse (A full circle/oval)
    QRectF rectEllipse(20.5, 20.5, 100.0, 100.0);
    painter.drawEllipse(rectEllipse);

    // Angles for partial curves:
    int startAngle {30 * CanvasWidget::SixteenthsOfADegree};  // Start at 30 degrees counter-clockwise from 3 o-clock
    int spanAngle {120 * CanvasWidget::SixteenthsOfADegree};  // Sweep for 120 degrees

    // 2. Arc (Just the outer stroked curve)
    QRectF rectArc(150.5, 20.5, 100.0, 100.0);
    painter.drawArc(rectArc, startAngle, spanAngle);

    // 3. Pie (Curve connected back to the center point, like a pizza slice)
    QRectF rectPie(20.5, 150.5, 100.0, 100.0);
    painter.drawPie(rectPie, startAngle, spanAngle);

    // 4. Chord (Curve with a straight line connecting its two endpoints)
    QRectF rectChord(150.5, 150.5, 100.0, 100.0);
    painter.drawChord(rectChord, startAngle, spanAngle);

    // --- Visualization helper ---
    // Let's draw the bounding boxes lightly so you can visually see
    // exactly how the bounding rectangles constrain the curves!
    painter.setPen(QPen(Qt::lightGray, 1, Qt::DashLine));
    painter.drawRect(rectEllipse);
    painter.drawRect(rectArc);
    painter.drawRect(rectPie);
    painter.drawRect(rectChord);
}