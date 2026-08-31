#include "canvaswidget.hpp"
#include <QPainter>
#include <QPixmap>

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

    // Let's create a 100x100 physical pixel pixmap
    QPixmap myPixmap(100, 100);
    myPixmap.fill(Qt::magenta);

    // 1. Draw it normally (Device Pixel Ratio = 1.0)
    // Qt maps 1 physical pixel of the pixmap to 1 logical pixel on screen.
    // It will render as 100x100 box.
    painter.drawPixmap(20, 50, myPixmap);
    painter.drawText(20, 40, "DevicePixelRatio: 1.0");

    // 2. High-DPI Handling
    // Let's copy our magenta box
    QPixmap highDpiPixmap {myPixmap};

    // Tell Qt: "This image has 2 physical pixels for every 1 logical pixel"
    // Tell Qt: "This image maps 2x2 physical pixels into 1 logical pixel"
    highDpiPixmap.setDevicePixelRatio(2.0);

    // Because its ratio is 2.0, Qt knows it is extremely dense.
    // Even though it is physically 100x100 pixels in memory, Qt will
    // automatically draw it into a 50x50 logical area on the screen to keep
    // it ultra-crisp!
    painter.drawPixmap(200, 50, highDpiPixmap);
    painter.drawText(200, 40, "DevicePixelRatio: 2.0");

    // Let's draw an exact 50x50 outline around it to prove Qt shrank it automatically
    painter.setPen(QPen(Qt::black, 2, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(200, 50, 50, 50);
}