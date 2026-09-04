#include <QGuiApplication>
#include "mrpainter.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    MrPainter mrPainter;
    mrPainter.run();

    return 0;
}
