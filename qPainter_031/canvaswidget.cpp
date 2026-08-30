#include "canvaswidget.hpp"
#include <QPainter>
#include <QPainterPath>
#include <QRectF>
#include <QPen>
#include <QBrush>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 400);
}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 1. Let's create a clipping path (a circle in the middle)
    QPainterPath clipPath;
    clipPath.addEllipse(QRectF(150, 50, 300, 300));

    // 2. Query State: Verify clipping is off by default
    bool beforeClip {painter.hasClipping()};

    // 3. Apply the clipping path
    painter.setClipPath(clipPath);

    // 4. Query State: Verify clipping is now ON.
    bool afterClip {painter.hasClipping()};

    // Draw the state to the top-left corner (NOTE: Because we are clipping to a circle)
    // in the center, we temporarily disable clipping to draw this text outside the circle!)
    painter.setClipping(false);
    painter.drawText(10, 20, QString("hasClipping() Before: %1").arg(beforeClip ? "true" : "false"));
    painter.drawText(10, 40, QString("hasClipping() After: %1").arg(afterClip ? "true" : "false"));

    // Re-enable our clipping region
    painter.setClipping(true);

    // 5. Draw a bunch of things that extend WAY outside the circle
    // Because clipping is on, only the pixels inside the circle will actually render!


    // A huge cyan background rectangle
    painter.fillRect(QRect(0, 0, width(), height()), Qt::cyan);

    // Some thick intersecting lines
    painter.setPen(QPen(Qt::darkBlue, 15));
    painter.drawLine(0, 0, width(), height());
    painter.drawLine(width(), 0, 0, height());

    // A massive rectangle stretching across the screen
    painter.setBrush(Qt::yellow);
    painter.setPen(QPen(Qt::black, 5));
    painter.drawRect(50, 150, 500, 100);

    // 6. Demonstrate restoring state
    // We remove the clip by disabling clipping explicitly, or if we had used
    // painter.save(), calling painter.restore() would also revert the clipping
    // region.
    painter.setClipping(false);

    // Draw a thin border to show the exact boundary of the clip path we just used
    painter.setPen(QPen(Qt::red, 2, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(clipPath);
}