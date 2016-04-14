#include <QApplication>
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
#include "examples/radiobuttonexamples.h"
#include "examples/checkboxexamples.h"
#include "examples/textfieldexamples.h"
#include "examples/listexamples.h"
#include "examples/avatarexamples.h"

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
      _radioButtonExamples(new RadioButtonExamples),
      _checkboxExamples(new CheckboxExamples),
      _textFieldExamples(new TextFieldExamples),
      _listExamples(new ListExamples),
      _avatarExamples(new AvatarExamples),
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
    if ("App Bar" == text) {
        _layout->setCurrentWidget(_appBarExamples);
    } else if ("Flat Button" == text) {
        _layout->setCurrentWidget(_flatButtonExamples);
    } else if ("Raised Button" == text) {
        _layout->setCurrentWidget(_raisedButtonExamples);
    } else if ("Icon Button" == text) {
        _layout->setCurrentWidget(_iconButtonExamples);
    } else if ("Tabs" == text) {
        _layout->setCurrentWidget(_tabsExamples);
    } else if ("Table" == text) {
        _layout->setCurrentWidget(_tableExamples);
    } else if ("Slider" == text) {
        _layout->setCurrentWidget(_sliderExamples);
    } else if ("Toggle" == text) {
        _layout->setCurrentWidget(_toggleExamples);
    } else if ("Radio Button" == text) {
        _layout->setCurrentWidget(_radioButtonExamples);
    } else if ("Checkbox" == text) {
        _layout->setCurrentWidget(_checkboxExamples);
    } else if ("Text Field" == text) {
        _layout->setCurrentWidget(_textFieldExamples);
    } else if ("List" == text) {
        _layout->setCurrentWidget(_listExamples);
    } else if ("Avatar" == text) {
        _layout->setCurrentWidget(_avatarExamples);
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
    _layout->addWidget(_radioButtonExamples);
    _layout->addWidget(_checkboxExamples);
    _layout->addWidget(_textFieldExamples);
    _layout->addWidget(_listExamples);
    _layout->addWidget(_avatarExamples);

    setCentralWidget(widget);
}

void MainWindow::_initMenu() const
{
    QMenu *file = new QMenu("&File");

    QAction *exitAction = file->addAction("E&xit");

    QMenu *components = new QMenu("&Components");
    QMenu *settings = new QMenu("&Settings");
    QMenu *examples = new QMenu("&Examples");
    QMenu *help = new QMenu("&Help");

    components->addAction("App Bar");
    components->addAction("Avatar");

    QMenu *buttons = new QMenu("Buttons");
    components->addMenu(buttons);

    buttons->addAction("Flat Button");
    buttons->addAction("Raised Button");
    buttons->addAction("Icon Button");

    components->addAction("Dialog");
    components->addAction("Menus");
    components->addAction("List");
    components->addAction("Slider");

    QMenu *switches = new QMenu("Switches");
    components->addMenu(switches);

    switches->addAction("Checkbox");
    switches->addAction("Radio Button");
    switches->addAction("Toggle");

    components->addAction("Table");
    components->addAction("Tabs");
    components->addAction("Text Field");

    menuBar()->addMenu(file);
    menuBar()->addMenu(components);
    menuBar()->addMenu(settings);
    menuBar()->addMenu(examples);
    menuBar()->addMenu(help);

    connect(components, SIGNAL(triggered(QAction *)), this, SLOT(showWidget(QAction *)));
    connect(exitAction, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
}
