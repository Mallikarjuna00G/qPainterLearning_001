#ifndef CANVASWIDGET_HPP
#define CANVASWIDGET_HPP

#include <QWidget>
#include <QPainter>

void drawMyArt(QPainter &painter);

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget() override;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void exportToSvg();
};
#endif // CANVASWIDGET_HPP
