#ifndef CANVASWIDGET_HPP
#define CANVASWIDGET_HPP

#include <QWidget>
#include <QPainter>

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget() override;

    void demoLinearGradient(QPainter &painter);
    void demoRadialGradient(QPainter &painter);
    void demoConicalGradient(QPainter &painter);
    void demoPadSpread(QPainter &painter);
    void demoRepeatSpread(QPainter &painter);
    void demoReflectSpread(QPainter &painter);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};
#endif // CANVASWIDGET_HPP
