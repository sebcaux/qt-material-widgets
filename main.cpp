#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include "style.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int id = QFontDatabase::addApplicationFont(":/fonts/Roboto-Regular.ttf");
    QFont font(QFontDatabase::applicationFontFamilies(id).at(0));
    font.setPixelSize(14);

    a.setFont(font);

    MainWindow w;
    w.show();

    return a.exec();
}
