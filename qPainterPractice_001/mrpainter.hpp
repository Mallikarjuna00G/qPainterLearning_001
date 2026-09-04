#ifndef MRPAINTER_HPP
#define MRPAINTER_HPP

#include <QObject>
#include <QPainter>
#include <QPainterPath>

class MrPainter : public QObject
{
    Q_OBJECT
public:
    explicit MrPainter(QObject *parent = nullptr);
    void run();

private:
    void paintIt(QPainter &painter, const QRect &rect);
    QPainterPath createRoundedCornerPolyline(const QPolygonF &points, qreal radius);
};

#endif // MRPAINTER_HPP
