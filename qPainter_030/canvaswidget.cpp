#include "canvaswidget.hpp"
#include <QPainter>
#include <QFont>
#include <QRectF>
#include <QString>

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

    QFont font(QFont("Arial", 12, QFont::Bold));
    painter.setFont(font);

    // 1. The Central Node
    QRectF node(250, 150, 100, 100);
    painter.setBrush(Qt::lightGray);
    painter.setPen(Qt::black);
    painter.drawRect(node);

    // Calculate the geometric anchors of node
    QPointF center {node.center()};
    QPointF north {QPointF(center.x(), node.top())};
    QPointF south {QPointF(center.x(), node.bottom())};
    QPointF east {QPointF(node.right(), center.y())};
    QPointF west {QPointF(node.left(), center.y())};

    // Draw the anchor points so we can see them
    painter.setBrush(Qt::red);
    painter.drawEllipse(center, 4, 4);
    painter.drawEllipse(north, 4, 4);
    painter.drawEllipse(south, 4, 4);
    painter.drawEllipse(east, 4, 4);
    painter.drawEllipse(west, 4, 4);

    // 2. Helper lambda to draw centered text at an anchor point
    auto drawLabel {
        [&](const QPointF& anchor, const QString& text, Qt::Alignment alignment) {
            // We calculate the logical bounding box for the text
            QRectF textBounds {painter.boundingRect(QRectF(0, 0, 1000, 1000), Qt::AlignLeft | Qt::AlignTop, text)};

            // We shift the text rectangle so that it aligns correctly with the anchor point!
            QRectF layoutRect {textBounds};

            if (alignment & Qt::AlignTop) {
                layoutRect.moveTop(anchor.y() + 5);  // +5 for padding
            } else if (alignment & Qt::AlignBottom) {
                layoutRect.moveBottom(anchor.y() - 5);
            } else if (alignment & Qt::AlignVCenter) {
                layoutRect.moveTop(anchor.y() - layoutRect.height() / 2);
            }

            if (alignment & Qt::AlignLeft) {
                layoutRect.moveLeft(anchor.x() + 5);
            } else if (alignment & Qt::AlignRight) {
                layoutRect.moveRight(anchor.x() - 5);
            } else if (alignment & Qt::AlignHCenter) {
                layoutRect.moveLeft(anchor.x() - layoutRect.width() / 2);
            }

            // Draw a faint yellow background so we can see the computed text box
            painter.fillRect(layoutRect, QColor(255, 255, 0, 100));

            // Finally draw the text exactly into our positioned rectangle
            painter.setPen(Qt::black);
            painter.drawText(layoutRect, Qt::AlignCenter, text);
        }
    };

    // 3. Attach labels to the anchors
    drawLabel(north, "North Label", Qt::AlignBottom | Qt::AlignHCenter);
    drawLabel(south, "South Label", Qt::AlignTop | Qt::AlignHCenter);
    drawLabel(east, "East Label", Qt::AlignLeft | Qt::AlignVCenter);
    drawLabel(west, "West Label", Qt::AlignRight | Qt::AlignVCenter);
    drawLabel(center, "Center", Qt::AlignVCenter | Qt::AlignHCenter);
}