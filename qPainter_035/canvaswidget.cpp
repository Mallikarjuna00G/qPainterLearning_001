#include "canvaswidget.hpp"
#include <QPainter>
#include <QPicture>

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

    // 1. Create out "recording device"
    QPicture picture;

    // 2. Create a separate painter to record commands into the QPicture
    QPainter picPainter;
    picPainter.begin(&picture);  // Start recording

    picPainter.setPen(QPen(Qt::blue, 3));
    picPainter.setBrush(Qt::yellow);
    picPainter.drawEllipse(0, 0, 100, 100);
    picPainter.setPen(Qt::black);
    picPainter.drawText(20, 55, "Recorded!");

    picPainter.end();  // Stop recording

    // 3. Save the exact sequence of commands to disk!
    // This doesn't save pixels; it saves the vector instructions.
    picture.save("my_drawing_commands.pic");

    // 4. Load those commands back from disk into a new QPicture
    QPicture loadedPicture;
    loadedPicture.load("my_drawing_commands.pic");

    // 5. Replay the commands onto our actual widget canvas!
    painter.drawText(20, 30, "Replaying original QPicture:");
    painter.drawPicture(20, 50, picture);

    // Let's replay the loaded one in a different spot
    painter.drawText(250, 30, "Replaying QPicture loaded from disk:");
    painter.drawPicture(250, 50, loadedPicture);

    // 6. We can even ask the picture how big the recorded drawing is!
    QRect picRect {picture.boundingRect()};

    // Let's draw a red bounding box around the second replay.
    // We must offset the bounding rect since we replayed the picture at (200, 50).
    picRect.translate(250, 50);

    painter.setPen(QPen(Qt::red, 2, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(picRect);
}