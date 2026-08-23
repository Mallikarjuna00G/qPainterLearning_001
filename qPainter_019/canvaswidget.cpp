#include "canvaswidget.hpp"
#include <QPainter>
#include <QPen>
#include <QTransform>
#include <QDebug>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{}

CanvasWidget::~CanvasWidget() = default;

void CanvasWidget::printMatrix(const QString &label, const QTransform &t)
{
    qDebug().noquote() << "===" << label << "===";

    // QTransform holds a 3x3 matrix
    // m11, m12, m13 (row1)
    // m21, m22, m23 (row2)
    // m31, m32, m33 (row3)
    qDebug().noquote() << QString("[%1, %2, %3]").arg(t.m11(), 6, 'f', 2).arg(t.m12(), 6, 'f', 2).arg(t.m13(), 6, 'f', 2);
    qDebug().noquote() << QString("[%1, %2, %3]").arg(t.m21(), 6, 'f', 2).arg(t.m22(), 6, 'f', 2).arg(t.m23(), 6, 'f', 2);
    qDebug().noquote() << QString("[%1, %2, %3]").arg(t.m31(), 6, 'f', 2).arg(t.m32(), 6, 'f', 2).arg(t.m33(), 6, 'f', 2);
}


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // We only want to print this once per paint event to avoid console spam
    static bool printed {false};
    if (!printed) {
        // 1. The default identity matrix (no transforms applied)
        QTransform t1 {painter.worldTransform()};
        printMatrix("1. Identity (default)", t1);

        // 2. Apply a Translation
        painter.translate(100, 50);
        QTransform t2 {painter.worldTransform()};
        printMatrix("2. After translate(100, 50)", t2);

        // 3. Apply a Scale on top of the translation
        painter.scale(2.0, 0.5);
        QTransform t3 {painter.worldTransform()};
        printMatrix("3. After scale(2.0, 0.5)", t3);

        // 4. Manual override using setWorldTransform
        QTransform manualTransform;
        manualTransform.translate(400, 400);  // Build the matrix offline
        manualTransform.rotate(45);  // Add rotation

        // BOOM! Obliterate whatever QPainter was doing and force our new matrix
        painter.setWorldTransform(manualTransform);
        QTransform t4 {painter.worldTransform()};
        printMatrix("4. Manual setWorldTransform", t4);

        // 5. Hard Reset!
        painter.resetTransform();
        QTransform t5 {painter.worldTransform()};
        printMatrix("5. After resetTransform", t5);

        printed = true;
    }

    // Let's actually draw something using our hard reset matrix just to prove
    // it went back to the top-left corner!
    painter.setBrush(Qt::yellow);
    painter.drawRect(0, 0, 50, 50);
    painter.drawText(10, 20, "I am at (0, 0)!");
}