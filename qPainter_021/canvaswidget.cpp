#include "canvaswidget.hpp"
#include <QPainter>
// #include <QLineF>  // For QLineF::fromPolar
#include <QtMath>  // we need this for qDegreesToRadians, qCos, and qSin

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 600);
}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 1. Set our logical window like we learned in qPainter_020
    int side {qMin(width(), height())};
    painter.setViewport((width() - side) / 2, (height() - side) / 2, side, side);
    painter.setWindow(-100, -100, 200, 200);  // (0, 0) is in the absolute center

    // 2. Draw the "Radar" rings
    painter.setPen(QPen(Qt::darkGreen, 1));
    painter.setBrush(Qt::black);
    painter.drawEllipse(QPointF(0, 0), 90, 90);  // Outer ring (radius 90)

    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(QPointF(0, 0), 60, 60);  // Middle ring (radius 60)
    painter.drawEllipse(QPoint(0, 0), 30, 30);  // Inner ring (radius 30)

    // 3. Draw dots perfectly spaced in a circle using QLineF::fromPolar!
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::green);

    // We want 12 dots spaced evenly around the outer ring (radius 80)
    // 360 degrees / 12 dots = 30 degrees per dot
    for (int angle {0}; angle < 360; angle += 30) {
        // --- USING INBUILT METHODS ---
        // Use Qt's Polar converter to generate an invisible line
        // NOTE: In Qt, 0 degrees is perfectly horizontal to the RIGHT,
        // and positive angles go CLOCKWISE (because Y goes down!)
        // QLineF polarLine {QLineF::fromPolar(90, angle)};

        // Grab the end point of that invisible line
        // QPointF dotPos {polarLine.p2()};

        // Draw our dot at the extracted point
        // painter.drawEllipse(dotPos, 3, 3);

        // -- USING HELPER METHOD ---
        // Pass our desired radius and angle in degrees into the helper
        QPointF dotPos {polarToCartesian(90, angle)};

        // Draw a tiny circle at the calculated X, Y position
        painter.drawEllipse(dotPos, 3, 3);
    }
}

QPointF CanvasWidget::polarToCartesian(qreal radius, qreal angleDegrees) const
{
    // C++ math functions use radians, not degrees! We must convert first
    qreal angleRadians {qDegreesToRadians(angleDegrees)};

    // Standard trigonometry to find X and Y
    qreal x {radius * qCos(angleRadians)};
    qreal y {radius * qSin(angleRadians)};

    return QPointF(x, y);
}