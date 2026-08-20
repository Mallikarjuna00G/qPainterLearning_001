#ifndef CANVASWIDGET_HPP
#define CANVASWIDGET_HPP

#include <QWidget>
#include <QResizeEvent>
#include <QPaintEvent>

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget() override;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief CanvasWidget::resizeEvent
     * Intercept the widget resize event to
     * take your custom actions.
     * @param event
     */
    void resizeEvent(QResizeEvent *event) override;
};
#endif // CANVASWIDGET_HPP
