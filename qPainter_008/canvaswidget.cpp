#include "canvaswidget.hpp"
#include <QPointF>
#include <QPen>
#include <QLineF>
#include <QList>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // --- 1. Batch Drawing Points ---
    batchDrawPoints(painter);

    // --- 2. Batch Drawing Lines ---
    batchDrawLines(painter);

}
void batchDrawPoints(QPainter &painter)
{
    // Prepare the points
    // Instead of calling drawPoint() 5 times, we pass a C-style array!
    // This is vastly more efficient for the graphics pipeline.
    constexpr int pointsCount {5};
    QPointF myPoints[pointsCount] {
        QPointF(50.5, 50.5),
        QPointF(100.5, 75.5),
        QPointF(150.5, 50.5),
        QPointF(200.5, 75.5),
        QPointF(250.5, 50.5)
    };

    // Prepare and select pen
    // Make the pen 10 pixels thick so we can actually see the points!
    painter.setPen(QPen(Qt::red, 10));

    // Draw using the pen (state)
    // Overload: drawPoints(const QPointF *points, int pointCount)
    painter.drawPoints(myPoints, pointsCount);
}

void batchDrawLines(QPainter &painter)
{
    // Let's draw a crosshatch pattern using a Qt List container

    // prepare a list of lines
    QList<QLineF> myLines;
    myLines.append(QLineF(50.5, 150.5, 250.5, 150.5));  // Horizontal 1
    myLines.append(QLineF(50.5, 200.5, 250.5, 200.5));  // Horizontal 2
    myLines.append(QLineF(100.5, 100.5, 100.5, 250.5));  // Vertical 1
    myLines.append(QLineF(200.5, 100.5, 200.5, 250.5));  // Vertical 2

    painter.setPen(QPen(Qt::blue, 3));
    // Overload: drawLines(const QList<QLineF> &lines)
    painter.drawLines(myLines);
}
