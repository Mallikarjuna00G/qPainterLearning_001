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

    // Create a thick pen so the pixels are obvious
    QPen thickPen(Qt::black);
    thickPen.setWidth(10);  // width = 10px
    painter.setPen(thickPen);

    // --- 1. Raw drawing (default) ---
    // Look closely at the edges of this line when you run it!
    painter.drawLine(50, 50, 250, 250);

    // --- 2. Smooth drawing (Antialiased) ---
    // Turn on the antialiasing render hint
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Draw the exact same line, just shifted to the right
    painter.drawLine(150, 50, 350, 250);
}