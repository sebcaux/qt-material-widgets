#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include "style.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/material/fonts/Roboto/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/material/fonts/Roboto/Roboto-Medium.ttf");
    QFontDatabase::addApplicationFont(":/material/fonts/Roboto/Roboto-Bold.ttf");

    QFontDatabase db;
    QFont font(db.font("Roboto", "Regular", 11));

    a.setFont(font);

    MainWindow w;
    w.show();

    return a.exec();
}
