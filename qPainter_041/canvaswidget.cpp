#include "canvaswidget.hpp"
#include <QPushButton>
#include <QPdfWriter>
#include <QMessageBox>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(400, 350);

    QPushButton *exportBtn {new QPushButton("Export to PDF", this)};
    exportBtn->move(140, 300);

    QObject::connect(exportBtn, &QPushButton::clicked, this, &CanvasWidget::exportToPdf);
}

CanvasWidget::~CanvasWidget() = default;


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter widgetPainter(this);
    widgetPainter.setRenderHint(QPainter::Antialiasing, true);

    // NOTE: Because our draw logic uses massive high-resolution coordinated
    // for the PDF, it would completely blow past out tiny 400x350 window!
    // To make it fit on screen, we scale the entire coordinate system down
    // by 10x!
    widgetPainter.scale(0.1, 0.1);

    drawMyArt(widgetPainter);
}

void CanvasWidget::exportToPdf()
{
    // 1. Setup the PDF writer (which lives in Qt6::Gui, so no extra CMake modules needed!)
    QPdfWriter pdfWriter("myDocument.pdf");

    // 2. Configure physical paper properties
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageMargins(QMarginsF(10, 10, 10, 10), QPageLayout::Millimeter);
    pdfWriter.setResolution(300);  // 300 Dots-Per-Inch for high-quality printing

    QPainter pdfPainter;
    pdfPainter.begin(&pdfWriter);

    // PAGE 1
    drawMyArt(pdfPainter);

    // PAGE 2
    pdfWriter.newPage();  // This explicitly creates a brand new blank page in PDF!
    pdfPainter.setPen(QPen(Qt::red, 50));
    pdfPainter.setBrush(Qt::transparent);
    pdfPainter.drawEllipse(150, 1000, 2000, 2000);  // Draw something different on page 2

    pdfPainter.end();

    QMessageBox::information(this, "Success", "my_document.pdf with 2 pages was created!");
}
void drawMyArt(QPainter &painter)
{
    // Because PDF printing resolution is extremely high, we must draw with
    // MASSIVE coordinates and extremely thick pens to make it visible!
    painter.setPen(QPen(Qt::darkBlue, 40, Qt::DashLine));
    painter.setBrush(Qt::cyan);
    painter.drawRect(200, 500, 2000, 1500);

    painter.setPen(QPen(Qt::black, 20));
    QFont font;
    font.setFamily("Arial");
    font.setBold(true);
    font.setPixelSize(160);
    painter.setFont(font);

    painter.drawText(300, 2400, "High-Res PDF Document!");
}
