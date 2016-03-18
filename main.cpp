#include "mainwindow.h"
#include <QApplication>
#include "style.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Style *style = new Style;
    a.setStyle(style);

    MainWindow w;
    w.show();

    return a.exec();
}
