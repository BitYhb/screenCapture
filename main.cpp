#include "src/view/widget.h"
#include <string>
#include <iostream>
#include <QApplication>

#include "src/core/screencapture.h"
#include "src/core/decodevideo.h"

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
