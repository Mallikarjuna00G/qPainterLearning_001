#include "canvaswidget.hpp"
#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QPen>
#include <QBrush>
#include <QLinearGradient>

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

    // 1. Create a simple mathematical wavy line (0 thickness)
    QPainterPath wavyLine;
    wavyLine.moveTo(50, 100);
    wavyLine.cubicTo(150, 100, 250, 0, 350, 100);

    // 2. Set up the Stroker
    QPainterPathStroker stroker;
    stroker.setWidth(30);  // We want a very thick 30px outline
    stroker.setCapStyle(Qt::RoundCap);  // Rounded ends

    // The stroker breaks curves into tiny straight lines to calculate the outline.
    // curveThreshold dictates how precise those tiny lines are.
    // Lower number = higher quality outline (default is 0.25).
    stroker.setCurveThreshold(0.1);

    // 3. Command the stroker to generate the new thick path!
    // This new path represents the actual geometry of the OUTLINE of the
    // wavy line.
    QPainterPath thickOutlinepath {stroker.createStroke(wavyLine)};

    // --- Drawing the results ---
    // Let's draw the generated outline as a filled shape using a cool gradient!
    QLinearGradient gradient(50, 0, 350, 0);
    gradient.setColorAt(0, Qt::red);
    gradient.setColorAt(1, Qt::blue);

    painter.setPen(Qt::NoPen);  // No border around the thick outline itself
    painter.setBrush(gradient);
    painter.drawPath(thickOutlinepath);  // We draw the OUTLINE path


    // Just to visualize what happened, let's draw the ORIGINAL 0-thickness line
    // in black on top!
    painter.setPen(QPen(Qt::black, 2, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(wavyLine);
}