#include <QMenu>
#include <QMenuBar>
#include <QStackedLayout>
#include <QDebug>
#include "mainwindow.h"
#include "examples/about.h"
#include "examples/flatbuttonexamples.h"
#include "examples/raisedbuttonexamples.h"
#include "examples/iconbuttonexamples.h"
#include "examples/appbarexamples.h"
#include "examples/tabsexamples.h"
#include "examples/tableexamples.h"
#include "examples/sliderexamples.h"
#include "examples/toggleexamples.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _layout(new QStackedLayout),
      _flatButtonExamples(new FlatButtonExamples),
      _raisedButtonExamples(new RaisedButtonExamples),
      _iconButtonExamples(new IconButtonExamples),
      _appBarExamples(new AppBarExamples),
      _tabsExamples(new TabsExamples),
      _tableExamples(new TableExamples),
      _sliderExamples(new SliderExamples),
      _toggleExamples(new ToggleExamples),
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
    } else if ("RaisedButton" == text) {
        _layout->setCurrentWidget(_raisedButtonExamples);
    } else if ("IconButton" == text) {
        _layout->setCurrentWidget(_iconButtonExamples);
    } else if ("Tabs" == text) {
        _layout->setCurrentWidget(_tabsExamples);
    } else if ("Table" == text) {
        _layout->setCurrentWidget(_tableExamples);
    } else if ("Slider" == text) {
        _layout->setCurrentWidget(_sliderExamples);
    } else if ("Toggle" == text) {
        _layout->setCurrentWidget(_toggleExamples);
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
    _layout->addWidget(_raisedButtonExamples);
    _layout->addWidget(_iconButtonExamples);
    _layout->addWidget(_appBarExamples);
    _layout->addWidget(_tabsExamples);
    _layout->addWidget(_tableExamples);
    _layout->addWidget(_sliderExamples);
    _layout->addWidget(_toggleExamples);

    setCentralWidget(widget);
}

void MainWindow::_initMenu() const
{
    QMenu *file = new QMenu("&File");
    QMenu *components = new QMenu("&Components");
    QMenu *settings = new QMenu("&Settings");
    QMenu *examples = new QMenu("&Examples");
    QMenu *help = new QMenu("&Help");

    components->addAction("AppBar");

    QMenu *buttons = new QMenu("Buttons");
    components->addMenu(buttons);

    buttons->addAction("FlatButton");
    buttons->addAction("RaisedButton");
    buttons->addAction("IconButton");

    components->addAction("Checkbox");
    components->addAction("Dialog");
    components->addAction("Menus");
    components->addAction("List");
    components->addAction("Slider");

    QMenu *switches = new QMenu("Switches");
    components->addMenu(switches);

    switches->addAction("CheckBox");
    switches->addAction("RadioButton");
    switches->addAction("Toggle");

    components->addAction("Table");
    components->addAction("Tabs");
    components->addAction("Textfield");

    menuBar()->addMenu(file);
    menuBar()->addMenu(components);
    menuBar()->addMenu(settings);
    menuBar()->addMenu(examples);
    menuBar()->addMenu(help);

    connect(components, SIGNAL(triggered(QAction *)), this, SLOT(showWidget(QAction *)));
}
