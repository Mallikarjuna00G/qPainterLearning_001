#ifndef CANVASWIDGET_HPP
#define CANVASWIDGET_HPP

#include <QWidget>

/**
 * @brief The CanvasWidget class
 * @note To use hardware acceleration, change the parent from `QWidget` to
 * `QOpenGLWidget`
 */
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
