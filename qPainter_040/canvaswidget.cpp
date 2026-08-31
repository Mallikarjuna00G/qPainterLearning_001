#include "canvaswidget.hpp"
#include <QPainter>
#include <QImage>
#include <QPushButton>
#include <QMessageBox>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(400, 350);
    QPushButton *exportBtn {new QPushButton("Export to PNG", this)};
    exportBtn->move(140, 300);

    QObject::connect(exportBtn, &QPushButton::clicked, this, &CanvasWidget::exportToPng);
}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter widgetPainter(this);
    widgetPainter.setRenderHint(QPainter::Antialiasing, true);

    // Draw to screen
    drawMyArt(widgetPainter);
}

void CanvasWidget::exportToPng()
{
    // 1. Allocate a blank pixel grid in memory
    QImage myImage(400, 300, QImage::Format_ARGB32);

    // Fill it with a background color (otherwise it defaults to random garbage pixels!)
    myImage.fill(Qt::white);

    // 3. Draw directly onto the image's pixels in memory
    QPainter imagePainter;
    imagePainter.begin(&myImage);

    // Let's turn on Anti-Aliasing for the image painter too so it looks smooth!
    imagePainter.setRenderHint(QPainter::Antialiasing, true);
    drawMyArt(imagePainter);
    imagePainter.end();

    // 4. The magic one-liner! Qt detects the .png extension and encodes the file
    myImage.save("my_rastor_art.png");

    QMessageBox::information(this, "Success", "my_rastor_art.png was saved!");
}

// 5. Our exact same shared drawing logic!
void drawMyArt(QPainter &painter)
{
    painter.setPen(QPen(Qt::darkBlue, 4, Qt::DashLine));
    painter.setBrush(Qt::cyan);
    painter.drawRect(50, 50, 200, 150);

    painter.setPen(Qt::red);
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(100, 100, 100, 100);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(60, 240, "Hello PNG World!");
}
