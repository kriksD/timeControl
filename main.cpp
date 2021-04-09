#include "timeControl.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    timeControl w;
    w.show();
    return a.exec();
}
