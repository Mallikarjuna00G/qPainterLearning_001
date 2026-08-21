#include "canvaswidget.hpp"
#include <QPainter>
#include <QFont>
#include <QFontInfo>
#include <QDebug>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Simply draw some reference x and y axis with a lighter pen
    painter.save();
    painter.setPen(QPen(Qt::lightGray, 1, Qt::DashLine));
    int xMid {width() / 2};
    int yMid {height() / 2};
    painter.drawLine(xMid, 0, xMid, height());
    painter.drawLine(0, yMid, width(), yMid);
    painter.restore(); // Go back to default black pen

    // Always turn on Antialiasing so text edges are perfectly smooth!
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    // --- 1. Set a custom font ---
    QFont fontCourierBold("Courier", 26, QFont::Bold);
    painter.setFont(fontCourierBold);

    // Let's inspect what we actually got using font() and fontInfo()!
    qDebug() << "Requested Font Family:" << painter.font().family();
    qDebug() << "Actual Rendered Font:" << painter.fontInfo().family();

    // --- 2 Measure the text (Crucial for Tikz nodes!) ---
    QString myText {"Hello Tikz Node!"};
    QFontMetrics metrics {painter.fontMetrics()};

    int textWidth {metrics.horizontalAdvance(myText)};
    int textHeight {metrics.height()};

    // --- 3. Calculate Geometrical Center (Top Left Corner of the Box) ---
    int topX {(width() - textWidth) / 2};
    int topY {(height() - textHeight) / 2};

    // Draw the box (adding 10px padding to all sides)
    painter.drawRect(topX - 10, topY - 10, textWidth + 20, textHeight + 20);

    // --- 4. Draw the text ---
    // The baseline is the geometric top (topY) PLUS the height of the letters (ascent)
    painter.drawText(topX, topY + metrics.ascent(), myText);
}