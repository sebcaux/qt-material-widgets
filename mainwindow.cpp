#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QStackedLayout>
#include <QDebug>
#include "mainwindow.h"
#include "components/flatbutton.h"
#include "components/iconbutton.h"
#include "components/appbar.h"
#include "examples/about.h"
#include "examples/flatbuttonexamples.h"
#include "examples/iconbuttonexamples.h"
#include "examples/appbarexamples.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _layout(new QStackedLayout),
      _flatButtonExamples(new FlatButtonExamples),
      _iconButtonExamples(new IconButtonExamples),
      _appBarExamples(new AppBarExamples),
      _about(new About)
{
    _initWidget();
    _initMenu();

    // -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-


    /*
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
    */
}

MainWindow::~MainWindow()
{
}

void MainWindow::showWidget(QAction *action)
{
    QString text(action->text());
    if ("AppBar" == text) {
        _layout->setCurrentWidget(_about);
    } else if ("FlatButton" == text) {
        _layout->setCurrentWidget(_flatButtonExamples);
    } else if ("IconButton" == text) {
        _layout->setCurrentWidget(_about);
    } else {
        _layout->setCurrentWidget(_about);
    }
}

void MainWindow::_initWidget()
{
    QWidget *widget = new QWidget;
    widget->setLayout(_layout);

    _layout->addWidget(_about);
    _layout->addWidget(_flatButtonExamples);

    setCentralWidget(widget);
}

void MainWindow::_initMenu() const
{
    QMenu *components = new QMenu("Components");
    components->addAction("AppBar");

    QMenu *buttons = new QMenu("Buttons");
    components->addMenu(buttons);

    buttons->addAction("FlatButton");
    buttons->addAction("IconButton");

    components->addAction("Tabs");

    menuBar()->addMenu(components);

    connect(components, SIGNAL(triggered(QAction *)), this, SLOT(showWidget(QAction *)));
}
