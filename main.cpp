#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("俄罗斯方块by~zzh");
    w.show();

    return a.exec();
}
