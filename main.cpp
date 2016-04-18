#include "mainwindow.h"
#include <QApplication>
#include <QCommonStyle>
#include "style.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QCommonStyle *style = new QCommonStyle;
//    a.setStyle(style);

//    a.setStyle(&Style::instance());

    MainWindow w;
    w.show();

    return a.exec();
}
