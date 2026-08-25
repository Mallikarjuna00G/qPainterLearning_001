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

    painter.setPen(QPen(Qt::darkBlue, 4));
    painter.setBrush(Qt::cyan);

    QPainterPath myPath;

    // 1. Move to the starting position (left side of the screen)
    myPath.moveTo(50, 200);

    // 2. A Quadratic Bezier Curve (quadTo)
    // A quadrative curve has ONE control point that "pulls" the line toward it.
    // quadTo(controlPointX, controlPointY, endPointX, endPointY);
    // We will pull the line up to (100, 50) and end the curve at (150, 200).
    myPath.quadTo(100, 50, 150, 200);


    // 3. A Cubic Bezier curve (cubicTo)
    // A cubic curve has TWO control points, allowing for S-curves.
    // cubicTo(ctrl1_X, ctrl1_Y, ctrl2_X, ctrl2_Y, endPointX, endPointY)
    // Let's create an "S" wave that dips down, then swoops back up!
    myPath.cubicTo(200, 350, 300, 50, 350, 200);

    // 4. Draw it!
    painter.drawPath(myPath);

    // --- OPTIONAL: Draw the control points so you can visualize the math! ---
    painter.setPen(QPen(Qt::red, 5));
    painter.drawPoint(100, 50);  // Control path for quadTo

    painter.setPen(QPen(Qt::magenta, 5));
    painter.drawPoint(200, 350);  // Control Point 1 for cubicTo
    painter.drawPoint(300, 50);  // Control point 2 for cubicTo
}