#include "mainwindow.h"
#include <QtWidgets/QVBoxLayout>
#include <qtmaterialavatar.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QtMaterialAvatar *avatars[3];
    avatars[0] = new QtMaterialAvatar(QImage("../qt-material-widgets/examples/assets/uxceo-128.jpg"));
    avatars[1] = new QtMaterialAvatar('W');
    avatars[2] = new QtMaterialAvatar(QIcon(":/icons/assets/ic_message_24px.svg"));

    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    widget->setLayout(layout);
    setCentralWidget(widget);

    layout->addWidget(avatars[0]);
    layout->addWidget(avatars[1]);
    layout->addWidget(avatars[2]);
}

MainWindow::~MainWindow()
{
}
