#include "canvaswidget.hpp"
#include <QPainter>
#include <QPen>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QConicalGradient>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(1200, 600);
}

CanvasWidget::~CanvasWidget() = default;

void CanvasWidget::demoLinearGradient(QPainter &painter)
{
    // Transitions colors along a straight line from Point A to Point B.
    // We define a diagonal vector from (50, 50) to (250, 250).

    QLinearGradient linearGradient(0, 50, 250, 250);
    linearGradient.setColorAt(0.0, Qt::blue);  // Start (0%)
    linearGradient.setColorAt(0.5, Qt::cyan);  // Middle (50%)
    linearGradient.setColorAt(1.0, Qt::darkBlue);  // End (100%)

    // We pass the gradient into the brush (which handles fills), not the Pen!
    painter.setBrush(linearGradient);
    painter.drawRect(0, 50, 200, 200);
    painter.drawText(0, 40, "1. QLinearGradient (Diagonal)");
}

void CanvasWidget::demoRadialGradient(QPainter &painter)
{
    // Radiates outward from a center point in a circle.
    // Parameters: Center (0, 150), Radius (100)

    QRadialGradient radialGradient(100, 150, 100);
    radialGradient.setColorAt(0.0, Qt::white);  // Hot center (0%)
    radialGradient.setColorAt(0.7, Qt::red);  // Glow (70%)
    radialGradient.setColorAt(1.0, Qt::darkRed);  // Outer edge (100%)

    painter.setBrush(radialGradient);

    // We draw an ellipse perfectly sized to the gradient's bounding box
    // to create a 3D sphere
    painter.drawEllipse(0, 50, 200, 200);
    painter.drawText(0, 40, "2. QRadialGradient (3D Sphere)");
}

void CanvasWidget::demoConicalGradient(QPainter &painter)
{
    // Sweeps colors around a central pivot point like a radar or color wheel.
    // Parameters: Center (100, 150), Start Angle (0 degrees)

    QConicalGradient conicalGradient(100, 150, 0);
    conicalGradient.setColorAt(0.0, Qt::magenta);
    conicalGradient.setColorAt(0.25, Qt::yellow);
    conicalGradient.setColorAt(0.5, Qt::cyan);
    conicalGradient.setColorAt(0.75, Qt::yellow);
    conicalGradient.setColorAt(1.0, Qt::magenta);  // Loop back to start color for a seemless blend.

    painter.setBrush(conicalGradient);
    painter.drawRect(0, 50, 200, 200);
    painter.drawText(0, 40, "3. QConicalGradient (ColorWheel)");
}

void CanvasWidget::demoPadSpread(QPainter &painter)
{
    // We make a very narrow horizontal linear gradient: from x=0 to x=50.
    QLinearGradient spreadGradient(0, 50, 50, 50);
    spreadGradient.setColorAt(0.0, Qt::green);
    spreadGradient.setColorAt(1.0, Qt::black);

    spreadGradient.setSpread(QGradient::PadSpread);

    painter.setBrush(spreadGradient);

    // PadSpread (the default) simply stretches the final color (black)
    // out to infinity to fill the rest of the shape!
    painter.drawRect(0, 50, 200, 200);
    painter.drawText(0, 40, "4A. QGradient::PadSpread");
}

void CanvasWidget::demoRepeatSpread(QPainter &painter)
{
    // We make a very narrow horizontal linear gradient: from x=0 to x=50.
    QLinearGradient spreadGradient(0, 50, 50, 50);
    spreadGradient.setColorAt(0.0, Qt::green);
    spreadGradient.setColorAt(1.0, Qt::black);

    spreadGradient.setSpread(QGradient::RepeatSpread);

    painter.setBrush(spreadGradient);

    // RepeatSpread hard-resets back to the start color (green) every 50 pixels!
    painter.drawRect(0, 50, 200, 200);
    painter.drawText(0, 40, "4B. QGradient::RepeatSpread");
}

void CanvasWidget::demoReflectSpread(QPainter &painter)
{
    // We make a very narrow horizontal linear gradient: from x=0 to x=50.
    QLinearGradient spreadGradient(0, 50, 50, 50);
    spreadGradient.setColorAt(0.0, Qt::green);
    spreadGradient.setColorAt(1.0, Qt::black);

    spreadGradient.setSpread(QGradient::ReflectSpread);

    painter.setBrush(spreadGradient);

    // ReflectSpread causes the gradient to bounce back and forth (Green->Black->Green)
    // to fill the entire shape!
    painter.drawRect(0, 50, 200, 200);
    painter.drawText(0, 40, "4C. QGradient::ReflectSpread");
}


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Give our shapes a clean black border
    painter.setPen(QPen(Qt::black, 2));

    painter.save();
    painter.translate(50, 0);
    // --- 1. LINEAR GRADIENT ---
    demoLinearGradient(painter);

    painter.translate(300, 0);
    // 2. RADIAL GRADIENT
    demoRadialGradient(painter);

    painter.translate(300, 0);
    // --- 3. CONICAL GRADIENT ---
    demoConicalGradient(painter);

    painter.restore();
    painter.translate(50, 300);
    // --- 4. SPREAD MODES (What if the shape is bigger than the gradient?)
    // --- 4A QGradient::PadSpread
    demoPadSpread(painter);

    painter.translate(300, 0);
    // --- 4B QGradient::RepeatSpread
    demoRepeatSpread(painter);

    painter.translate(300, 0);
    // --- 4C QGradient::ReflectSpread
    demoReflectSpread(painter);

    painter.restore();
}