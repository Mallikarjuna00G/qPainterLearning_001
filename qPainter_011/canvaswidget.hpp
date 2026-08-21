#ifndef CANVASWIDGET_HPP
#define CANVASWIDGET_HPP

#include <QWidget>
#include <QPointF>
#include <QPainter>
#include <QRectF>

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    static constexpr int SixteenthsOfADegree {16};

    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget() override;

    inline QRectF determineBoundingBox(const QPointF &center, qreal radius) {
        return QRectF(
            center.x() - radius,
            center.y() - radius,
            radius * 2.0,
            radius * 2.0
        );
    }
    inline QRectF drawArcIntuitive(QPainter &painter, const QPointF &center, qreal radius, qreal startAngle, qreal spanAngle) {
        QRectF boundingBox {determineBoundingBox(center, radius)};
        painter.drawArc(boundingBox, startAngle * SixteenthsOfADegree, spanAngle * SixteenthsOfADegree);
        return boundingBox;
    }
    inline QRectF drawChordIntuitive(QPainter &painter, const QPointF &center, qreal radius, qreal startAngle, qreal spanAngle) {
        QRectF boundingBox {determineBoundingBox(center, radius)};
        painter.drawChord(boundingBox, startAngle * SixteenthsOfADegree, spanAngle * SixteenthsOfADegree);
        return boundingBox;
    }
    inline QRectF drawPieIntuitive(QPainter &painter, const QPointF &center, qreal radius, qreal startAngle, qreal spanAngle) {
        QRectF boundingBox {determineBoundingBox(center, radius)};
        painter.drawPie(boundingBox, startAngle * SixteenthsOfADegree, spanAngle * SixteenthsOfADegree);
        return boundingBox;
    }

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};
#endif // CANVASWIDGET_HPP
