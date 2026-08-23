#ifndef CANVASWIDGET_HPP
#define CANVASWIDGET_HPP

#include <QWidget>
#include <QPainter>
#include <QString>

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget() override;

    /**
     * @brief drawGridAndRect A helper function so we can draw the exact same
     * shape multiple times
     * @param painter
     * @param label
     */
    void drawGridAndRect(QPainter &painter, const QString &label);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};
#endif // CANVASWIDGET_HPP
