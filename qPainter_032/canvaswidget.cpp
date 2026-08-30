#include "canvaswidget.hpp"
#include <QPainter>
#include <QRectF>
#include <QColor>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    // Important: To actually see the "Clear" composition mode work properly
    // and punch a hole through to the background, we need to eensire the widget
    // itself supports transparency!
    setAttribute(Qt::WA_TranslucentBackground);
    resize(900, 300);
}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Draw a faint grid so we can see when a hole is punched through to
    // transparency
    painter.fillRect(rect(), QColor(240, 240, 240));

    // A helper lambda to draw our test case
    auto drawCompositionTest {
        [&](int xOffset, QPainter::CompositionMode mode, const QString& title) {
            painter.save();
            painter.translate(xOffset, 50);

            // 1. Draw the DESTINATION (The pixels already on the canvas)
            // We use the default mode (SourceOver) to lay down the base square
            painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
            painter.setBrush(Qt::blue);
            painter.setPen(Qt::NoPen);
            painter.drawRect(50, 50, 100, 100);

            // 2. Change the composition mode!
            painter.setCompositionMode(mode);

            // 3. Draw the SOURCE (The new pixels being added)
            // We draw a red circle that overlaps the top-left corner of the
            // blue square. We give it 50% opacity (127/255) so we can see how
            // blending behaves
            painter.setBrush(QColor(255, 0, 0, 127));
            painter.drawEllipse(25, 25, 100, 100);

            // Draw the title
            painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
            painter.setPen(Qt::black);
            painter.drawText(20, 180, title);

            painter.restore();
        }
    };

    // Test 1: SourceOver (Default) - The Semi-transparent red circle blends
    // OVER the blue square
    drawCompositionTest(0, QPainter::CompositionMode_SourceOver, "1. SourceOver (Default)");

    // Test 2: Source - The red circle completely REPLACES the blue square pixels it touches
    drawCompositionTest(300, QPainter::CompositionMode_Source, "2. Source (Replace)");

    // Test 3: Clear - The circle acts as an ERASER, wiping out the blue square and leaving a hole!
    drawCompositionTest(600, QPainter::CompositionMode_Clear, "3. Clear (Eraser)");
}