#ifndef CANVASWIDGET_HPP
#define CANVASWIDGET_HPP

#include <QWidget>
#include <QPointF>

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget() override;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    /**
     * @brief polarToCartesian Converts (Radius, Angle) into a standard (X, Y) point
     * @param radius
     * @param angleDegrees
     * @return
     */
    QPointF polarToCartesian(qreal radius, qreal angleDegrees) const;
};
#endif // CANVASWIDGET_HPP
