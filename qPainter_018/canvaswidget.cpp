#include "canvaswidget.hpp"
#include <QPen>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(1200, 720);
}

CanvasWidget::~CanvasWidget() = default;

void CanvasWidget::drawGridAndRect(QPainter &painter, const QString &label)
{
    // Draw a light gray crosshair to show where (0, 0) currently is!
    painter.setPen(QPen(Qt::lightGray, 1, Qt::DashLine));
    painter.drawLine(-1000, 0, 1000, 0);  // X-axis
    painter.drawLine(0, -1000, 0, 1000);  // Y-axis

    // Draw a prominent red dot exactly at the current (0, 0) origin
    painter.setPen(QPen(Qt::red, 6));
    painter.drawPoint(0, 0);

    // Draw our square starting exactly at the origin (0, 0)
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::cyan);

    // NOTICE: We always pass the exact same raw coordinates!
    painter.drawRect(0, 0, 100, 100);

    // Draw the label slightly above the square
    painter.setPen(Qt::black);
    painter.drawText(0, -10, label);
}


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // --- 1. BASE (no transform) ---
    painter.save();
    // We translate 50px away from the top-left edge just so we can see it clearly.
    painter.translate(50, 50);
    drawGridAndRect(painter, "1. Normal");
    painter.restore();

    // --- 2. TRANSLATE ---
    painter.save();
    // Shifts (0, 0) origin by dx and dy pixels
    painter.translate(300, 50);
    drawGridAndRect(painter, "2. translate(300, 50)");
    painter.restore();

    // --- 3. SCALE ---
    painter.save();
    // Translate first to get to our new drawing spot...
    painter.translate(550, 50);

    // scale(sx, sy) multiplies the grid size.
    // 1.5 makes it 50% wider. 0.5 makes it half tall.
    // Notice how this also scales the pen width and the font size!
    painter.scale(1.5, 0.5);

    drawGridAndRect(painter, "3. scale(1.5, 0.5)");
    painter.restore();

    // --- 4. ROTATE ---
    painter.save();
    // Translate down to the second row
    painter.translate(100, 300);

    // rotate(angle) spins the coordinates system clockwise in DEGREES
    // around (0, 0). Notice how the entire square swings down because
    // it pivots around its top-left corner!
    painter.rotate(45);

    drawGridAndRect(painter, "4. rotate(45)");
    painter.restore();

    // --- 5. SHEAR ---
    painter.save();
    painter.translate(400, 300);

    // shear(sh, sv) skews the coordinate system (like italisizing a font).
    // A horizontal shear (sh) shifts the X coordinates based on their Y
    // position.
    painter.shear(0.5, 0.0);  // Lean to the right

    drawGridAndRect(painter, "5. shear(0.5, 0.0)");
    painter.restore();
}