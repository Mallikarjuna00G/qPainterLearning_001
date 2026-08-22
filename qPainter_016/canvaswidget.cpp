#include "canvaswidget.hpp"
#include <QPainter>
#include <QPen>
#include <QBrush>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Setup a thick black pen for the borders so we can clearly see the edges
    painter.setPen(QPen(Qt::black, 3));

    // --- 1. STANDARD PATTERN BRUSH (transparent background) ---
    // We create a brush using Qt::CrossPattern. The grid lines will be blue.
    // By default, the space between the lines is completely transparent
    // (Qt::TransparentMode), so the widget's default white (or gray) window
    // color shows through.

    QBrush crossBrush(Qt::blue, Qt::CrossPattern);
    painter.setBrush(crossBrush);

    painter.drawRect(50, 50, 200, 200);
    painter.drawText(50, 40, "1. Transparent Background (Default)");

    // --- 2. OPAQUE BACKGROUND MODE ---
    // We keep the exact same blue CrossPattern brush.
    // But we change the Background Mode to opaque, and set the background
    // color to yellow. Now, the "empty space" between the blue lines is
    // forcefully filled with yellow!

    painter.save();  // Save state so that we don't permanently alter the painter's background mode.

    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.setBackground(QBrush(Qt::yellow));  // The "fill" for the empty space

    painter.drawRect(300, 50, 200, 200);
    painter.drawText(300, 40, "2. OpaqueMode (Yellow background)");

    painter.restore();  // Restores back to Qt::TransparentMode

    // --- 3. BRUSH ORIGIN (The "Wallpaper" effect) ---
    // By default, brush patterns are universally anchored to (0, 0) of the
    // window.
    // If you draw a shape, it acts like a shading window revealing the
    // static wallpaper behind it.

    painter.setBrush(QBrush(Qt::darkRed, Qt::DiagCrossPattern));

    // Shape 3A: default origin
    // Look closesly at the top-left corner of the black border. The pattern
    // lines will intersect it randomly based on where the shape sits in
    // the window.

    painter.drawRect(50, 350, 200, 200);
    painter.drawText(50, 340, "3A. Default Origin (Anchored to Window 0, 0)");

    // Shape 3B: Custom Origin
    // We move the brush origin to perfectly match the top-left coordinate
    // of this shape. Look at the top-left corner here: The pattern perfectly
    // anchors to the corner!
    painter.save();

    painter.setBrushOrigin(300, 350);  // Set anchor to the shape's X,Y
    painter.drawRect(300, 350, 200, 200);
    painter.drawText(300, 340, "3B: Custom origin (Anchored to Shape)");

    painter.restore();
}