#include <QApplication>
#include <QDebug>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(resources);

    /*QFont font = a.font();
    font.setPointSize(font.pointSize() * 2);
    a.setFont(font);*/

    MainWindow window;
    window.show();

    return QApplication::exec();
}
