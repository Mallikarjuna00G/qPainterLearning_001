#include "canvaswidget.hpp"
#include <QPainter>
#include <QElapsedTimer>
#include <QImage>
#include <QRandomGenerator>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(800, 400);
}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // We will draw 10,000 semi-transparent circles to test CPU performance
    int iterations {10000};

    // 1. Un-premultilied Alpha (Standard, but mathematically heavy for blending)
    QImage slowImage(400, 400, QImage::Format_ARGB32);
    slowImage.fill(Qt::transparent);
    QPainter slowPainter(&slowImage);
    slowPainter.setPen(Qt::NoPen);
    slowPainter.setBrush(QColor(255, 0, 0, 50));  // Semi-transparent red

    QElapsedTimer timer1;
    timer1.start();
    for (int i {0}; i < iterations; ++i) {
        int x {QRandomGenerator::global()->bounded(400)};
        int y {QRandomGenerator::global()->bounded(400)};
        slowPainter.drawEllipse(x, y, 20, 20);
    }
    slowPainter.end();
    qint64 slowTime {timer1.elapsed()};

    // 2. Premultiplied Alpha (Qt's highly optimized fast-path for alpha blending)
    QImage fastImage(400, 400, QImage::Format_ARGB32_Premultiplied);
    fastImage.fill(Qt::transparent);
    QPainter fastPainter(&fastImage);
    fastPainter.setPen(Qt::NoPen);
    fastPainter.setBrush(QColor(0, 0, 255, 50));  // Semi-transparent blue

    QElapsedTimer timer2;
    timer2.start();
    for (int i {0}; i < iterations; ++i) {
        int x {QRandomGenerator::global()->bounded(400)};
        int y {QRandomGenerator::global()->bounded(400)};
        fastPainter.drawEllipse(x, y, 20, 20);
    }
    fastPainter.end();
    qint64 fastTime {timer2.elapsed()};

    // Draw the generated benchmark images to the screen
    painter.drawImage(0, 0, slowImage);
    painter.drawImage(400, 0, fastImage);

    // Draw the timing results
    painter.setPen(Qt::black);
    painter.drawText(20, 30, QString{"Format_ARGB32 (Slow): %1 ms"}.arg(slowTime));
    painter.drawText(420, 30, QString{"Format_ARGB32_Premultiplied (Fast): %1 ms"}.arg(fastTime));
}