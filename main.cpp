#include "src/widget.h"
#include <string>
#include <iostream>
#include <QApplication>

#include "src/screencapture.h"
#include "src/decodevideo.h"

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
