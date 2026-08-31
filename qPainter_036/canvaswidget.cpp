#include "canvaswidget.hpp"
#include <QPainter>
#include <QPixmap>
#include <QImage>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(500, 300);
}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // Notice we do NOT set Antialiasing right away!

    // Let's create a very tiny 10x10 "pixel art" image
    QImage tinyImage(10, 10, QImage::Format_RGB32);
    tinyImage.fill(Qt::white);

    // Draw a basic smiley face pixel by pixel
    tinyImage.setPixelColor(2, 2, Qt::black);
    tinyImage.setPixelColor(7, 2, Qt::black);
    tinyImage.setPixelColor(2, 7, Qt::black);
    tinyImage.setPixelColor(3, 8, Qt::black);
    tinyImage.setPixelColor(4, 8, Qt::black);
    tinyImage.setPixelColor(5, 8, Qt::black);
    tinyImage.setPixelColor(6, 8, Qt::black);
    tinyImage.setPixelColor(7, 7, Qt::black);

    QPixmap tinyPixmap {QPixmap::fromImage(tinyImage)};

    // 1. Draw it scaled up by 15x WITHOUT SmoothPixmapTransform
    // By default, Qt uses Nearest-Neighbor interpolation.
    // This preserves hard pixel edges perfectly.
    painter.drawText(20, 30, "Default (Nearest-Neighbor)");
    painter.drawPixmap(20, 50, 150, 150, tinyPixmap);

    // 2. Turn ON SmoothPixmapTransform
    // Now we instruct Qt to use Bilinear interpolation when scaling!
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    painter.drawText(250, 30, "SmoothPixmapTransform (Bilinear)");
    // It will draw the same tiny pixmap scaled up by 15x, but it will blur and blend
    // the pixels to try and make it look smooth instead of blocky.
    painter.drawPixmap(250, 50, 150, 150, tinyPixmap);
}