#include "canvaswidget.hpp"
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QBrush>

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

    painter.setPen(QPen(Qt::darkBlue, 4));
    painter.setBrush(QBrush(Qt::cyan));

    // Create a 5-pointed star path!
    // The lines of the star intersect each other in the middle.
    QPainterPath starPath;
    starPath.moveTo(0, -50);
    starPath.lineTo(30, 40);
    starPath.lineTo(-45, -15);
    starPath.lineTo(45, -15);
    starPath.lineTo(-30, 40);
    starPath.closeSubpath();

    // --- 1. OddEvenFill (The default) ---
    painter.save();
    painter.translate(150, 150);
    // Explicitly set the rule (even though it's the default)
    starPath.setFillRule(Qt::OddEvenFill);
    painter.drawPath(starPath);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(-50, 80, "OddEvenFill");
    painter.restore();

    // --- 2. WindingFill ---
    painter.save();
    painter.translate(450, 150);
    // Change the rule
    starPath.setFillRule(Qt::WindingFill);
    painter.drawPath(starPath);

    painter.setPen(Qt::black);
    painter.drawText(-50, 80, "WindingFill");
    painter.restore();
}