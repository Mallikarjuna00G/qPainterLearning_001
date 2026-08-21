#include "canvaswidget.hpp"
#include <QPainter>
#include <QPen>
#include <QRectF>
#include <QList>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(Qt::darkMagenta, 3));

    // 1. Single standard rectangle
    QRectF rect1(20.0, 20.0, 100.0, 100.0);
    painter.drawRect(rect1);

    // 2. Batch drawing rectangles
    // If you are rendering a grid or hundreds of boxes, ALWAYS use
    // drawRects instead of a loop
    QList<QRectF> batchRects {
        QRectF(150.0, 20.0, 40.0, 40.0),
        QRectF(200.0, 20.0, 40.0, 40.0),
        QRectF(250.0, 20.0, 40.0, 40.0)
    };
    painter.drawRects(batchRects);

    // 3. Rounded rectangle (Absolute Size)
    // The curve radii (xRadius, yRadius) are measured strictly in pixels.
    QRectF rectRoundedAbs(20.0, 150.0, 100.0, 60.0);
    painter.drawRoundedRect(rectRoundedAbs, 15.0, 15.0, Qt::AbsoluteSize);

    // 4. Rounded rectangle (relative size)
    // The curve radii are measured as a PERCENTAGE (0.0 to 100.0) of half
    // the rectangle's width/height.
    // 100% relative curve creates a perfect "pill" shape (or a circle if
    // it's a square)!
    QRectF rectRoundedRel(150.0, 150.0, 100.0, 100.0);
    painter.drawRoundedRect(rectRoundedRel, 100.0, 100.0, Qt::RelativeSize);

    // just for fun, let's draw an elliptical rounded rect!
    // X curve is 100%, Y curve is 20%
    QRectF rectRoundedWeird(280.0, 150.0, 100.0, 60.0);
    painter.drawRoundedRect(rectRoundedWeird, 100.0, 20.0, Qt::RelativeSize);

    QRectF rectRoundedRel2(150.0, 350.0, 200.0, 100.0);
    painter.drawRoundedRect(rectRoundedRel2, 50.0, 100.0, Qt::RelativeSize);

    QRectF rectRoundedRel3(450.0, 250.0, 100.0, 200.0);
    painter.drawRoundedRect(rectRoundedRel3, 50.0, 100.0, Qt::RelativeSize);

    // simply writing the bounding boxes
    painter.setPen(QPen(Qt::lightGray, 3, Qt::DotLine));
    painter.drawRect(rect1);
    painter.drawRects(batchRects);
    painter.drawRect(rectRoundedAbs);
    painter.drawRect(rectRoundedRel);
    painter.drawRect(rectRoundedWeird);
    painter.drawRect(rectRoundedRel2);
    painter.drawRect(rectRoundedRel3);
}