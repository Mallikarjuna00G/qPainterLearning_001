#include "canvaswidget.hpp"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QRectF>
#include <QString>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // --- Approach 2: QPainter::boundingRect ---
    painter.save();
    painter.translate(350, 50);  // Moved to the right side of the canvas

    // Switch to a smaller font so the paragraph fits nicely in the column!
    QFont bodyFont("Arial", 14);
    painter.setFont(bodyFont);

    // We want to force the text to fit into a 200px wide column. The height
    // (1000) is just an arbitrarily large number to give it infinite
    // room to wrap downwards.
    QRectF columnConstraint(0, 0, 200, 1000);

    // Create a much longer string to test wrapping
    QString longText {"This is a really long string that we want to constrain into a small 200px wide bounding box. Notice how Qt automatically calculates the line breaks!"};

    // Set the layout flags: WordWrap + AlignTop + AlignLeft
    int flags {Qt::TextWordWrap | Qt::AlignTop | Qt::AlignLeft};

    // Simulate the drawing to get the resulting bounding box!
    QRectF wrappedBox {painter.boundingRect(columnConstraint, flags, longText)};

    // Let's visualize it!
    // 1. Draw the constraint column in light gray dashes
    painter.setPen(QPen(Qt::lightGray, 1, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(columnConstraint);

    // 2. Draw the actual consumed bounds in blue
    painter.setPen(QPen(Qt::blue, 2));
    painter.drawRect(wrappedBox);

    // 3. Draw the text inside our column constraint
    painter.setPen(Qt::black);
    // Notice we use the same conatraint box and flags when actually drawing!
    painter.drawText(columnConstraint, flags, longText);

    painter.restore();
}