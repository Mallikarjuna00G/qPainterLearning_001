#include "canvaswidget.hpp"
#include <QPainter>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    // Open the painting pipeline
    QPainter painter(this);

    // Query the dynamic size of the widget
    // `width()` and `height()` are inherited from `QWidget`
    int currentWidth = width();
    int currentHeight = height();

    // Draw an 'X' that connects the dynamic corners of the screen
    painter.drawLine(0, 0, currentWidth, currentHeight);  // Top-Left to Bottom-Right
    painter.drawLine(currentWidth, 0, 0, currentHeight);  // Top-Right to Bottom-Left
}