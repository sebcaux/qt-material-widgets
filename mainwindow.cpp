#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include "mainwindow.h"
#include "flatbutton.h"
#include "iconbutton.h"
#include "appbar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenu *components = new QMenu("Components");
    components->addAction("AppBar");

    QMenu *buttons = new QMenu("Buttons");
    components->addMenu(buttons);

    buttons->addAction("FlatButton");
    buttons->addAction("IconButton");

    menuBar()->addMenu(components);

    // -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-

    QVBoxLayout *layout = new QVBoxLayout;
    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);

    AppBar *appBar = new AppBar;
    layout->addWidget(appBar);

    QPushButton *button1 = new QPushButton("Test #1");
    layout->addWidget(button1);

    FlatButton *flatButton = new FlatButton;
    flatButton->setText("My button");

    QIcon icon("../qt-material-widgets/face.svg");
    flatButton->setIcon(icon);
    flatButton->setIconSize(QSize(64, 64));

    layout->addWidget(flatButton);

    // -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-

    QHBoxLayout *hLayout = new QHBoxLayout;
    QLabel *label = new QLabel("Hello");
    label->setMaximumHeight(32);

    IconButton *iconButton = new IconButton(icon);
    iconButton->setText("My button sis afdadsfadsf adsfasdf");
    iconButton->setIconSize(QSize(32, 32));

    hLayout->addWidget(iconButton);
    hLayout->addWidget(label);

    layout->addLayout(hLayout);

    // -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-

    QPushButton *button2 = new QPushButton("Test #2");
    layout->addWidget(button2);
    button2->setIcon(icon);

    // -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
}

MainWindow::~MainWindow()
{
}
