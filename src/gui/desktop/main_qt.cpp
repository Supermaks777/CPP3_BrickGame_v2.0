#include "gui/desktop/qt_viewer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTViewer w;
    w.show();
    return a.exec();
}
