#include "mainwindow.h"
#include <QApplication>
#include "style.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QFontDatabase db;
    //QFont font(db.font("Roboto", "Regular", 11));
    //a.setFont(font);

    MainWindow w;
    w.show();

    return a.exec();
}
