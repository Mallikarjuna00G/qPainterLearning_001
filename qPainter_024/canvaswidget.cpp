#include "canvaswidget.hpp"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPainterPath>

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

    // Set a very thick pen and a bright brush
    painter.setPen(QPen(Qt::darkBlue, 10, Qt::DashLine));
    painter.setBrush(Qt::yellow);

    // Create a simple triangle path centered at (0, 0).
    QPainterPath trianglePath;
    trianglePath.moveTo(0, -50);
    trianglePath.lineTo(50, 50);
    trianglePath.lineTo(-50, 50);
    trianglePath.closeSubpath();

    // --- 1. drawPath() ---
    painter.save();
    painter.translate(100, 150);
    // drawPath uses BOTH the Pen (for the outline) and the Brush (for the fill)
    painter.drawPath(trianglePath);
    painter.restore();

    // --- 2. strokePath() ---
    painter.save();
    painter.translate(300, 150);
    // strokePath ONLY uses the Pen (for the outline). It completely ignores
    // the Brush.
    // It takes two arguments: the path, and the Pen you want to use.
    painter.strokePath(trianglePath, painter.pen());
    painter.restore();

    // --- 3. fillPath() ---
    painter.save();
    painter.translate(500, 150);
    // fillPath ONLY uses the Brush (for the inside). It completely ignores
    // the Pen.
    // It takes two arguments: the path, and the Brush you want to use.
    painter.fillPath(trianglePath, painter.brush());
    painter.restore();

    // Optional: Add labels
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(60, 250, "drawPath()");
    painter.drawText(250, 250, "strokePath()");
    painter.drawText(460, 250, "fillPath()");
}