#include "mainwindow.h"
#include <QApplication>
#include "style.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle(new Style);

    MainWindow w;
    w.show();

    return a.exec();
}
