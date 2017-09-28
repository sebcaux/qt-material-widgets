#include "mainwindow.h"
#include <QtWidgets/QVBoxLayout>
#include <QtGui/QIcon>
#include <qtmaterialavatar.h>
#include <QDebug>
#include <lib/qtmaterialtheme.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QtMaterialAvatar *avatars[3];
    avatars[0] = new QtMaterialAvatar(QImage(":/images/assets/uxceo-128.jpg"));
    avatars[1] = new QtMaterialAvatar('W');
    avatars[2] = new QtMaterialAvatar(QIcon(QtMaterialTheme::icon("communication", "message")));

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
