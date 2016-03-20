#include <QMenu>
#include <QMenuBar>
#include <QStackedLayout>
#include <QDebug>
#include "mainwindow.h"
#include "examples/about.h"
#include "examples/flatbuttonexamples.h"
#include "examples/iconbuttonexamples.h"
#include "examples/appbarexamples.h"
#include "examples/tabsexamples.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _layout(new QStackedLayout),
      _flatButtonExamples(new FlatButtonExamples),
      _iconButtonExamples(new IconButtonExamples),
      _appBarExamples(new AppBarExamples),
      _tabsExamples(new TabsExamples),
      _about(new About)
{
    _initWidget();
    _initMenu();
}

MainWindow::~MainWindow()
{
}

void MainWindow::showWidget(QAction *action)
{
    QString text(action->text());
    if ("AppBar" == text) {
        _layout->setCurrentWidget(_appBarExamples);
    } else if ("FlatButton" == text) {
        _layout->setCurrentWidget(_flatButtonExamples);
    } else if ("IconButton" == text) {
        _layout->setCurrentWidget(_iconButtonExamples);
    } else if ("Tabs" == text) {
        _layout->setCurrentWidget(_tabsExamples);
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
    _layout->addWidget(_iconButtonExamples);
    _layout->addWidget(_appBarExamples);
    _layout->addWidget(_tabsExamples);

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

    components->addAction("Checkbox");
    components->addAction("Dialog");
    components->addAction("Menus");
    components->addAction("List");
    components->addAction("Slider");
    components->addAction("Switches");
    components->addAction("Table");
    components->addAction("Tabs");
    components->addAction("Textfield");

    menuBar()->addMenu(components);

    connect(components, SIGNAL(triggered(QAction *)), this, SLOT(showWidget(QAction *)));
}
