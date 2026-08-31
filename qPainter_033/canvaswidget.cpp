#include "canvaswidget.hpp"
#include <QPainter>
#include <QPixmap>
#include <QImage>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(500, 500);
}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 1. Create a QImage programmatically (A 100x100 checkerboard)
    // QImage is optimized for direct pixel access.
    QImage myImage(100, 100, QImage::Format_RGB32);
    for (int y {0}; y < 100; ++y) {
        for (int x {0}; x < 100; ++x) {
            // If both x and y are in 10x10 block parity, make it black else white
            bool isBlack {(x / 10) % 2 == (y / 10) % 2};
            myImage.setPixelColor(x, y, isBlack ? Qt::black : Qt::white);
        }
    }

    // 2. Create a QPixmap from the QImage
    // QPixmap is highly optimized for showing images on screen.
    QPixmap myPixmap {QPixmap::fromImage(myImage)};

    // --- DRAWING ---

    // A. drawImage()
    // Slower for rendering than QPixmap, but useful if the image pixels are constantly changing.
    painter.drawImage(20, 20, myImage);
    painter.drawText(20, 140, "drawImage()");

    // B. drawPixMap()
    // Extremely fast. This is the standard way to render static assets in UI.
    painter.drawPixmap(200, 20, myPixmap);
    painter.drawText(200, 140, "drawPixMap()");

    // C. drawTiledPixmap()
    // Takes a small pixmap and repeats it indefinitely to fill a larger rectangle!
    // This is incredibly efficient for drawing textures or repeating backgrounds.
    painter.drawTiledPixmap(10, 200, 400, 200, myPixmap);
    painter.drawText(20, 420, "drawTiledPixmap() filling a 400x200 rect");
}