#include "canvaswidget.hpp"
#include <QPainter>
#include <QFont>
#include <QFontMetricsF>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 300);
}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 1. Define our font and text
    QFont myFont {QFont("Arial", 36, QFont::Bold)};
    painter.setFont(myFont);
    QString myText {"Hello QPainter!"};

    // 1. Approach 1: QFontMetricsF
    // QFontMetricsF is analytical class that can measure text before
    // QPainter even exists!
    painter.save();
    painter.translate(50, 100);

    QFontMetricsF metrics(myFont);
    // Measure the exact bounding box required to render this string
    QRectF logicalBox {metrics.boundingRect(myText)};
    QRectF tightBox {metrics.tightBoundingRect(myText)};

    // Draw the logical box in red
    painter.setPen(QPen(Qt::blue, 3, Qt::DashLine));
    painter.drawRect(logicalBox);

    // Draw the tight box in green
    painter.setPen(Qt::red);
    painter.drawRect(tightBox);

    // Draw the text in black
    painter.setPen(Qt::black);
    // We draw the text at (0, 0), which means the text uses (0, 0) as
    // its baseline origin.
    // The tightBox naturally accounts for this!
    painter.drawText(0, 0, myText);

    // Optional: reference baseline
    painter.drawLine(0, 0, 300, 0);
    painter.restore();
}