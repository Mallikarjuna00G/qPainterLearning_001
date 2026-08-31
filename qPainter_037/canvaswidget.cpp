#include "canvaswidget.hpp"
#include <QPainter>
#include <QString>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(800, 400);
}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // A helper lambda to query and print the current render hints
    auto printHints {
        [&painter](int yPos, const QString& label) {
            // We can query the entire bitmask
            QPainter::RenderHints hints {painter.renderHints()};

            // ... and test specific flags!
            // Alternatively, you can use painter.testRenderHint(QPainter::Antialiasing)
            bool isAA {hints.testFlag(QPainter::Antialiasing)};
            bool isSmooth {hints.testFlag(QPainter::SmoothPixmapTransform)};
            bool isTextAA {hints.testFlag(QPainter::TextAntialiasing)};

            QString text {QString{"%1 -> Antialiasing: %2, SmoothPixmap: %3, TextAntialiasing: %4"}
                             .arg(label)
                             .arg(isAA ? "ON" : "OFF")
                             .arg(isSmooth ? "ON" : "OFF")
                             .arg(isTextAA ? "ON" : "OFF")
            };
            painter.drawText(20, yPos, text);
        }
    };

    painter.setPen(Qt::black);

    // Default state
    printHints(30, "State 1 (Default)");

    // Turn on Antialiasing
    painter.setRenderHint(QPainter::Antialiasing, true);
    printHints(70, "State 2 (Antialiasing = true)");

    // Turn on SmoothPixmapTransform
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    printHints(110, "State 3 (SmoothPixMap = true)");

    // Turn off Antialiasing
    painter.setRenderHint(QPainter::Antialiasing, false);
    printHints(150, "State 4 (Antialiasing = false)");
}