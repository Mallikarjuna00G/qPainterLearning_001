#include "canvaswidget.hpp"
#include <QPainter>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(1200, 720);  // Initial physical window
}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 1. THE VIEWPORT (Physical Screen Pixels)
    // By default, the viewport is the exact pizel size of the widget.
    // Let's explicitly set it just to be clear. We want to use the whole widget.
    int side {qMin(width(), height())};  // Keep it a perfect square
    // Center our square viewport inside the widget if it gets stretched into a rectangle.
    painter.setViewport((width() - side) / 2, (height() - side) / 2, side, side);

    // 2. THE WINDOW (Logical Coordinates)
    // We declare that our mathematical world goes from -50 to +50 on both
    // axes. The top-left corner is at (-50, 50), and it is 100 units wide
    // and 100 units tall.
    // This perfectly places (0, 0) at the exact center!
    painter.setWindow(-50, -50, 100, 100);

    // From this point on, we draw using our LOGICAL coordinates.
    // We never think about physical pixels again!

    // Draw an X and Y axis to prove where (0, 0) is
    painter.setPen(QPen(Qt::lightGray, 0));  // A width of 0 means "1 cosmetic pixel" regardless of scaling!
    painter.drawLine(-50, 0, 50, 0);  // X-axis
    painter.drawLine(0, -50, 0, 50);  // Y-axis

    // Draw a prominent red dot at our logical origin (0, 0)
    painter.setPen(QPen(Qt::red, 2));  // 2 logical units wide
    painter.drawPoint(0, 0);

    // Draw a square in the center!
    // It goes from x = -20, y = -20, and is 40 units wide/tall
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(Qt::cyan);
    painter.drawRect(-20, -20, 40, 40);
}