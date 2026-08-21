#include "canvaswidget.hpp"
#include <QPainter>
#include <QPen>
#include <QRectF>
#include <QFont>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setFont(QFont("Arial", 16, QFont::Bold));

    QPen penBoundingBox(Qt::darkGray, 1, Qt::DashLine);
    // Create a bounding box so we can visually see how the text behaves inside it
    QRectF boundingBox1(50.0, 50.0, 400.0, 50.0);
    painter.setPen(penBoundingBox);
    painter.drawRect(boundingBox1);

    QPen penText(Qt::blue);
    // 1. Default (Left to right)
    painter.setLayoutDirection(Qt::LeftToRight);
    painter.setPen(penText);
    // We explicitly ask for Qt::AlignLeft
    painter.drawText(boundingBox1, Qt::AlignLeft | Qt::AlignVCenter, "Left-To-Right (Qt::AlignLeft)");

    // Create a second bounding box directly below the first
    QRectF boundingBox2(50.0, 150.0, 400.0, 50.0);
    painter.setPen(penBoundingBox);
    painter.drawRect(boundingBox2);

    QPen penText2(Qt::red);
    // 2. Right to Left
    painter.setLayoutDirection(Qt::RightToLeft);
    painter.setPen(penText2);
    // We explicitly ask for Qt::AlightLeft again!
    // But notice how it snaps to the RIGHT side of the box because the
    // layout direction inverted it.
    painter.drawText(boundingBox2, Qt::AlignLeft | Qt::AlignVCenter, "Right-To-Left (Qt::AlignLeft)");

    // Create a third bounding box directly below the second
    QRectF boundingBox3(50.0, 250.0, 400.0, 50.0);
    painter.setPen(penBoundingBox);
    painter.drawRect(boundingBox3);

    // 3. The "Gotcha" (Right to Left WITHOUT alignment flags)
    painter.setLayoutDirection(Qt::RightToLeft);
    painter.setPen(penText2);
    // We do not pass any alignment flags here!
    // Notice how it completely IGNORES the RightToLeft layout direction and snaps
    // to the LEFT. This is because omitting flags causes Qt to fallback to a default
    // QTextOption object which is hardcoded to Left-To-Right!
    painter.drawText(boundingBox3, "Right-To-Left (No Flags Fallback)");
}