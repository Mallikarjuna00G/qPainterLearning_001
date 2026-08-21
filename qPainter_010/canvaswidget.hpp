#ifndef CANVASWIDGET_HPP
#define CANVASWIDGET_HPP

#include <QWidget>

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    static constexpr int SixteenthsOfADegree {16};

    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget() override;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};
#endif // CANVASWIDGET_HPP
