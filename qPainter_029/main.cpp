#include "canvaswidget.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CanvasWidget w;
    w.show();
    return QApplication::exec();
}
