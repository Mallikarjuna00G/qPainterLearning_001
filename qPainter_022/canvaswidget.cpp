#include "canvaswidget.hpp"
#include <QPainter>
#include <QPainterPath>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(400, 400);
}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(Qt::black, 3));
    painter.setBrush(Qt::cyan);  // Notice we are setting a brush!

    // --- Constructing the path ---
    QPainterPath myPath;

    // 1. Move our invisible pen to the top-center without drawing anything
    myPath.moveTo(200, 50);

    // 2. Draw a straight line down to the bottom-right
    myPath.lineTo(350, 350);

    // 3. Draw a straight line straight across to the bottom-left
    myPath.lineTo(50, 350);

    // 4. We could draw a line back to (200, 50)...
    // OR we can just tell the path to automatically snap shut!
    myPath.closeSubpath();

    myPath.addEllipse(150, 150, 100, 100);


    // --- DRAWING PATH ---
    // At this point, myPath is just an invisble mathematical concept in memory.
    // We have to explicitly hand it to QPainter to render it into the screen.
    painter.drawPath(myPath);
}