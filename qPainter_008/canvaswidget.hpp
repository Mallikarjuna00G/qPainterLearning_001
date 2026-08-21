#ifndef CANVASWIDGET_HPP
#define CANVASWIDGET_HPP

#include <QWidget>
#include <QPainter>

void batchDrawPoints(QPainter &painter);
void batchDrawLines(QPainter &painter);

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget() override;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};
#endif // CANVASWIDGET_HPP
