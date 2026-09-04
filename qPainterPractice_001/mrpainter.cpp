#include "mrpainter.hpp"
#include <QPainterPath>
#include <QPen>
#include <QFont>
#include <QDir>
#include <QPolygonF>
#include <QPointF>
#include <QVector2D>

MrPainter::MrPainter(QObject *parent)
    : QObject{parent}
{}

void MrPainter::run()
{
    QSize size2K {2560, 1440};
    QRect rect2K {QPoint(0, 0), size2K};

    QPainter painter;
    QImage image(size2K, QImage::Format_RGB32);
    painter.begin(&image);
    paintIt(painter, rect2K);
    QDir().mkdir("outImages");
    image.save("outImages/image.png");

    painter.end();
}

void MrPainter::paintIt(QPainter &painter, const QRect &rect)
{
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(rect, Qt::white);

    painter.save();

    painter.translate(rect.width() / 2, rect.height() / 2);

    QPen thickPen(QPen(Qt::black, 8));
    thickPen.setJoinStyle(Qt::RoundJoin);
    thickPen.setCapStyle(Qt::RoundCap);

    QPolygonF polygonPoints;
    polygonPoints << QPoint(0, 0)
                  << QPoint(0, 200)
                  << QPoint(100, 325)
                  << QPoint(200, 200)
                  << QPoint(200, 0)
                  << QPoint(0, 200)
                  << QPoint(200, 200)
                  << QPoint(0, 0)
                  << QPoint(200, 0);
    QPainterPath path {createRoundedCornerPolyline(polygonPoints, 50)};
    QPainterPath path2;
    path2.addPolygon(polygonPoints);

    painter.setPen(thickPen);
    painter.scale(2.0, 2.0);
    painter.drawPath(path);

    painter.translate(-300, -300);
    painter.drawPath(path2);

    painter.restore();
}

QPainterPath MrPainter::createRoundedCornerPolyline(const QPolygonF &points, qreal radius)
{
    QPainterPath path;
    if (points.count() < 2) {
        if (points.count() == 1) {
            path.moveTo(points.first());
        }
        return path;
    }

    // Start the path at the first point
    path.moveTo(points.first());

    // Loop through all the "middle" points (the corners)
    for (int i {1}; i < points.count(); ++i) {
        QPointF p0 {points[i - 1]};  // Previous point
        QPointF p1 {points[i]};  // The sharp corner
        QPointF p2 {points[i + 1]};  // Next point

        // Calculate unit vectors pointing AWAY from the corner towards the previous and next points
        QVector2D v1 {p0 - p1};
        QVector2D v2 {p2 - p1};
        v1.normalize();
        v2.normalize();

        // Safety check: ensure we don't try to curve further than half the length of the line itself
        qreal maxRadius1 {QVector2D(p0 - p1).length() / 2.0};
        qreal maxRadius2 {QVector2D(p2 - p1).length() / 2.0};
        qreal actualRadius {qMin(radius, qMin(maxRadius1, maxRadius2))};

        // Calculate where the corner should start and end
        QPointF curveStart {p1 + (v1 * actualRadius).toPointF()};
        QPointF curveEnd {p1 + (v2 * actualRadius).toPointF()};

        // 1. Draw straight line stopping just before the corner
        path.lineTo(curveStart);

        // 2. Round the corner using quadTo!
        path.quadTo(p1, curveEnd);
    }

    // Finish the path by drawing to the very last point
    path.lineTo(points.last());

    return path;
}
