#ifndef CANVASWIDGET_HPP
#define CANVASWIDGET_HPP

#include <QWidget>

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget() override;

private:
    /**
     * @brief printMatrix A helper function to print the 3x3 matrix in a
     * readable format
     * @param label
     * @param t
     */
    void printMatrix(const QString &label, const QTransform &t);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};
#endif // CANVASWIDGET_HPP
