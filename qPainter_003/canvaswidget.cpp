#include "canvaswidget.hpp"
#include <QPainter>
#include <QDebug>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int currentWidth {width()};
    int currentHeight {height()};

    painter.drawLine(0, 0, currentWidth, currentHeight);
    painter.drawLine(currentWidth, 0, 0, currentHeight);
}

void CanvasWidget::resizeEvent(QResizeEvent *event)
{
    // The QResizeEvent object carries data about the new size.
    // Let's log it to the console to prove we intercepted it!
    qDebug() << "Resize fired!! New Size:" << event->size().width() << "x" << event->size().height();

    /**
     * @warning It is crucial Qt best practice to pass the event up to
     * the base class, so `QWidget` can handle any internal housekeeping
     * it needs to do.
     */
    QWidget::resizeEvent(event);
}