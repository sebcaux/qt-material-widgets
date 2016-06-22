#include "mainwindow.h"
#include <QPainter>
#include <QVBoxLayout>
#include "components/flatbutton.h"
#include "components/raisedbutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QWidget *widget = new QWidget;

    widget->setLayout(layout);
    setCentralWidget(widget);

//    FlatButton *button = new FlatButton;
//    button->setText("Hello");
//
//    layout->addWidget(button);

    RaisedButton *button;

    button = new RaisedButton;
    button->setText("Hello");

    layout->addWidget(button);
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.setPen(Qt::red);

    painter.drawRect(rect());
}

/*
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QStackedLayout>
#include <QStringBuilder>
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
#include "examples/menuexamples.h"
#include "examples/iconmenuexamples.h"
#include "components/fab.h"
#include "components/snackbar.h"
#include "components/dialog.h"

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
      _menuExamples(new MenuExamples),
      _iconMenuExamples(new IconMenuExamples),
      _about(new About)
{
    _initWidget();
    _initMenu();

    FloatingActionButton *button = new FloatingActionButton(QIcon("../qt-material-widgets/ic_local_dining_white_24px.svg"));
    button->setParent(this);

    button->setCorner(Qt::TopRightCorner);
    button->setMini(true);
    button->setYOffset(56);

    //

    new FloatingActionButton(QIcon("../qt-material-widgets/ic_message_white_24px.svg"), this);

    //button2->setDisabled(true);

    snackbar = new Snackbar;
    snackbar->setParent(this);

    //

    QPushButton *btn = new QPushButton;
    btn->setText("Show Snackbar");
    btn->setGeometry(90, 50, 140, 40);
    btn->setParent(this);

    connect(btn, SIGNAL(pressed()), this, SLOT(addMsg()));

    btn = new QPushButton;
    btn->setText("Show Snackbar (instant)");
    btn->setGeometry(240, 50, 140, 40);
    btn->setParent(this);

    connect(btn, SIGNAL(pressed()), this, SLOT(addInstantMsg()));

    //

    {
        Dialog *dialog = new Dialog;
        dialog->setParent(this);

        FlatButton *btn = new FlatButton;
        btn->setMinimumHeight(40);
        btn->setText("Hello world");

        QPushButton *btn2 = new QPushButton;
        btn2->setText("Hello world");

        QVBoxLayout *layout = new QVBoxLayout;
        dialog->setWindowLayout(layout);

        layout->addWidget(btn);
        layout->addWidget(btn2);

        {
            QPushButton *btn;

            btn = new QPushButton;
            btn->setParent(this);
            btn->setText("Show");
            btn->setGeometry(190, 80, 140, 40);

            QObject::connect(btn, SIGNAL(pressed()), dialog, SLOT(showDialog()));

            btn = new QPushButton;
            btn->setParent(this);
            btn->setText("Hide");
            btn->setGeometry(370, 80, 140, 40);

            QObject::connect(btn, SIGNAL(pressed()), dialog, SLOT(hideDialog()));
        }
    }

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
    } else if ("Menu" == text) {
        _layout->setCurrentWidget(_menuExamples);
    } else if ("Icon Menu" == text) {
        _layout->setCurrentWidget(_iconMenuExamples);
    } else {
        _layout->setCurrentWidget(_about);
    }
}

static int n = 1;

void MainWindow::addMsg()
{
    snackbar->addMessage(QString("Hello from the Snackbar (") % QString::number(n++) % QString(")"));
}

void MainWindow::addInstantMsg()
{
    QString msg("This is longer message which will show up immediately after it is added to the message queue");
    msg.append(QString(" (") % QString::number(n++) % QString(")."));

    snackbar->addMessage(msg, true);
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
    _layout->addWidget(_menuExamples);
    _layout->addWidget(_iconMenuExamples);

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

    QMenu *menus = new QMenu("Menus");
    components->addMenu(menus);

    menus->addAction("Menu");
    menus->addAction("Icon Menu");
    menus->addAction("Drop Down Menu");

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
*/
