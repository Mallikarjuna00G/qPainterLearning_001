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

    // We will draw a horizontal line in the middle
    int xCenter {width() / 2};
    int yCenter {height() / 2};

    // 1. The isolated red line
    painter.save();  // Push current state (default 1px black pen) to the stack

    // Create a new pen
    QPen thickRedPen(Qt::red);
    thickRedPen.setWidth(5);  // width = 5px

    // switch to new pen (state)
    painter.setPen(thickRedPen);

    // Draw a thick red line on the left side
    painter.drawLine(0, yCenter, xCenter, yCenter);

    // Switch back to previous state (pen)
    painter.restore();

    // Draw on the right side
    painter.drawLine(xCenter, yCenter, width(), yCenter);
}