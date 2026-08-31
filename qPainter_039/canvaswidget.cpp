#include "canvaswidget.hpp"
#include <QSvgGenerator>
#include <QFont>
#include <QPushButton>
#include <QMessageBox>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(400, 350);

    // Create an export button
    QPushButton *exportBtn {new QPushButton("Export to SVG", this)};
    exportBtn->move(140, 300);  // Position it at the bottom

    // Connect the button to our custom slot
    connect(exportBtn, &QPushButton::clicked, this, &CanvasWidget::exportToSvg);
}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter widgetPainter(this);
    widgetPainter.setRenderHint(QPainter::Antialiasing, true);

    // 2. Draw our art to the screen whenever the OS requests a visual update
    drawMyArt(widgetPainter);
}

void CanvasWidget::exportToSvg()
{
    // 3. Setup the SVG generator only when the user clicks the button!
    QSvgGenerator svgGen;
    svgGen.setFileName("my_vector_art.svg");
    svgGen.setSize(QSize(400, 300));  // Sets the physical/default dimensions of the document (e.g. width="400" height="300")
    svgGen.setViewBox(QRect(0, 0, 400, 300));  // Defines the internal coordinate system so the vectors can scale infinitely without cropping
    svgGen.setTitle("QPainter SVG Demo");
    svgGen.setDescription("An SVG file generated purely by QPainter code!");

    QPainter svgPainter;
    svgPainter.begin(&svgGen);

    // 4. Run the exact same drawing logic onto the SVG painter!
    drawMyArt(svgPainter);

    svgPainter.end();  // File is finalized and written to disk here!

    // Show a popup letting the user know it succeeded
    QMessageBox::information(this, "Success", "my_vector_art.svg was saved successfully!");
}
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
    painter.drawText(60, 240, "Hello SVG World!");
}
