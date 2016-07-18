#include "mainwindow.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include "components/flatbutton.h"
#include "components/raisedbutton.h"
#include "components/drawer.h"
#include "components/menu.h"
#include "lib/testrippleoverlay.h"
#include "lib/transparencyproxy.h"
#include "lib/sizeproxy.h"
#include "components/appmenu.h"
#include "xx/qtmaterialflatbutton.h"
#include "lib/sizeproxywidget.h"
#include "yy/flatbuttonsettingseditor.h"
#include "yy/raisedbuttonsettingseditor.h"
#include "yy/fabsettingseditor.h"
#include "components/raisedbutton.h"
#include "xx/qtmaterialfab.h"
#include "ui_flatbuttonsettingsform.h"
#include "ui_fabsettingsform.h"
#include "yy/avatarsettingseditor.h"
#include "yy/badgesettingseditor.h"
#include "components/menuplus.h"
#include "components/menuplusproxy.h"
//#include "components/iconbutton.h"
#include "xx/qtmaterialiconbutton.h"
//#include "components/iconmenuplus.h"
#include "xx/qtmaterialiconmenu.h"
#include "components/textfield.h"
#include "xx/qtmaterialmenuitem.h"
//#include "components/selectfieldplus.h"
#include "xx/qtmaterialselectfield.h"
#include "yy/selectfieldsettingseditor.h"
#include "yy/iconmenusettingseditor.h"
#include "yy/checkboxsettingseditor.h"
#include "yy/radiobuttonsettingseditor.h"
#include "components/circularprogress.h"
#include "yy/circularprogresssettingseditor.h"
#include "yy/progresssettingseditor.h"
#include "components/textfield.h"
#include "components/dialog.h"
#include "yy/textfieldsettingseditor.h"
#include "components/tabs.h"
#include "xx/qtmaterialtabs.h"
#include "components/slider.h"
#include "components/toggle.h"
#include "xx/qtmaterialslider.h"
#include "yy/slidersettingseditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _menu(new MenuPlus)
{
    SliderSettingsEditor *editor = new SliderSettingsEditor;
    setCentralWidget(editor);

    return;

    //TextFieldSettingsEditor *editor = new TextFieldSettingsEditor;
    //setCentralWidget(editor);

    //return;

    //ProgressSettingsEditor *editor = new ProgressSettingsEditor;
    //setCentralWidget(editor);

    //return;

    //CircularProgressSettingsEditor *editor = new CircularProgressSettingsEditor;
    //setCentralWidget(editor);

    //return;

    //RadioButtonSettingsEditor *editor = new RadioButtonSettingsEditor;
    //setCentralWidget(editor);

    //return;

    //CheckBoxSettingsEditor *editor = new CheckBoxSettingsEditor;
    //setCentralWidget(editor);

    //return;

    //IconMenuSettingsEditor *editor = new IconMenuSettingsEditor;
    //setCentralWidget(editor);

    //return;

    //SelectFieldSettingsEditor *editor = new SelectFieldSettingsEditor;
    //setCentralWidget(editor);

    //return;

    //FlatButtonSettingsEditor *fb = new FlatButtonSettingsEditor;
    //setCentralWidget(fb);

    //return;

    //RaisedButtonSettingsEditor *fb = new RaisedButtonSettingsEditor;
    //setCentralWidget(fb);

    //return;

    //FloatingActionButtonSettingsEditor *fb = new FloatingActionButtonSettingsEditor;
    //setCentralWidget(fb);

    //return;

    //AvatarSettingsEditor *fb = new AvatarSettingsEditor;
    //setCentralWidget(fb);

    //BadgeSettingsEditor *ed = new BadgeSettingsEditor;
    //setCentralWidget(ed);


    _menu->addMenuItem("Menu item #1");
    _menu->addMenuItem("Menu item #2");
    _menu->addMenuItem("Menu item #3");
    //menu->setFixedSize(200, 250);
    _menu->setMaximumHeight(250);
    _menu->setMinimumWidth(300);

    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    widget->setLayout(layout);
    setCentralWidget(widget);

    widget->setStyleSheet("QWidget { background: white; }");


    Slider *sldr = new Slider;
    Slider *sldr2 = new Slider;
    QtMaterialSlider *sldr3 = new QtMaterialSlider;

    Toggle *tgl = new Toggle;

    layout->addStretch();
    layout->addWidget(sldr);
    layout->addWidget(sldr2);
    layout->addWidget(sldr3);
    layout->addWidget(tgl);
    layout->addStretch();

    return;

    QStackedLayout *stack = new QStackedLayout;
    stack->addWidget(new QLabel("<center>First</center>"));
    stack->addWidget(new QLabel("<center>Second</center>"));
    stack->addWidget(new QLabel("<center>Third</center>"));

    Tabs *tabs = new Tabs;
    layout->addWidget(tabs);
    layout->addLayout(stack);
    layout->setContentsMargins(0, 0, 0, 0);

    tabs->addTab("First", QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
    tabs->addTab("Second", QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
    tabs->addTab("Third", QIcon("../qt-material-widgets/ic_star_black_24px.svg"));

    //

    QtMaterialTabs *_tabs = new QtMaterialTabs;
    layout->addWidget(_tabs);
    layout->setContentsMargins(0, 0, 0, 0);

    _tabs->addTab("First", QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
    _tabs->addTab("Second", QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
    _tabs->addTab("Third", QIcon("../qt-material-widgets/ic_star_black_24px.svg"));

    QStackedLayout *stack2 = new QStackedLayout;
    stack2->addWidget(new QLabel("<center>First</center>"));
    stack2->addWidget(new QLabel("<center>Second</center>"));
    stack2->addWidget(new QLabel("<center>Third</center>"));

    layout->addLayout(stack2);

    connect(_tabs, SIGNAL(currentChanged(int)), stack2, SLOT(setCurrentIndex(int)));

    /*
    QtMaterialIconButton *btn = new QtMaterialIconButton(QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
    layout->addWidget(btn);

    layout->addStretch();

    //CircularProgress *cp = new CircularProgress;
    //layout->addWidget(cp);

    TextField *tf = new TextField;
    layout->addWidget(tf);
    layout->addStretch();

    Dialog *dlg = new Dialog;
    dlg->setParent(this);

    //dlg->windowLayout()->addWidget(new QPushButton("Hello"));
    QVBoxLayout *dl = new QVBoxLayout;
    dl->addWidget(new QPushButton("Hello"));
    dlg->setWindowLayout(dl);

    QPushButton *bbbtn = new QPushButton("Show dialog");
    layout->addWidget(bbbtn);

    connect(bbbtn, SIGNAL(pressed()), dlg, SLOT(showDialog()));

    QtMaterialIconMenu *im = new QtMaterialIconMenu(QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
    layout->addWidget(im);
    layout->setAlignment(im, Qt::AlignCenter);

    {
        im->addMenuItem("C");
        im->addMenuItem("C++");
        im->addMenuItem("Haskell");
        im->addMenuItem("JavaScript");
        im->addMenuItem("ECMAScript");
        im->addMenuItem("OCaml");
        im->addMenuItem("Python");
        im->addMenuItem("F#");
        im->addMenuItem("Clojure");
        im->addMenuItem("Java");
    }

    QtMaterialSelectField *sfp = new QtMaterialSelectField;
    //sfp->setBackgroundColor(Qt::white);
    layout->addWidget(sfp);
    layout->setAlignment(sfp, Qt::AlignCenter);

    {
        sfp->addItem("C");
        sfp->addItem("C++");
        sfp->addItem("Haskell");
        sfp->addItem("JavaScript");
        sfp->addItem("ECMAScript");
        sfp->addItem("OCaml");
        sfp->addItem("Python");
        sfp->addItem("F#");
        sfp->addItem("Clojure");
        sfp->addItem("Java");
    }

    layout->addStretch();
    */

    //layout->setAlignment(sfp, Qt::AlignCenter);

    //TextField *tf = new TextField;
    //tf->setBackgroundColor(Qt::white);
    //tf->setLabel("This is label");
    //tf->setPlaceholderText("What is this");
    //layout->addWidget(tf);

    //layout->setAlignment(tf, Qt::AlignCenter);

    /*
    {
        QtMaterialMenuItem *b;

        b = new QtMaterialMenuItem;
        b->setText("Hello 123");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Select everything");
        b->setIcon(QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Run something");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Download internet");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Done");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Run something");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Download internet");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Done");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Select everything");
        b->setIcon(QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Run something");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Download internet");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Done");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Run something");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Download internet");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Done");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Select everything");
        b->setIcon(QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Run something");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Download internet");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Done");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Run something");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Download internet");
        im->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Done");
        im->addMenuItem(b);
    }

    */

    /*
    //layout->addWidget(_menu);

    layout->setAlignment(im, Qt::AlignCenter);

    //

    QSlider *slider1 = new QSlider(Qt::Horizontal);
    slider1->setParent(this);
    slider1->setGeometry(10, 10, 400, 20);
    slider1->setRange(0, 100);
    slider1->setValue(100);

    QSlider *slider2 = new QSlider(Qt::Horizontal);
    slider2->setParent(this);
    slider2->setGeometry(10, 30, 400, 20);
    slider2->setRange(0, 100);
    slider2->setValue(100);

    QSlider *slider3 = new QSlider(Qt::Horizontal);
    slider3->setParent(this);
    slider3->setGeometry(10, 50, 400, 20);
    slider3->setRange(0, 100);
    slider3->setValue(100);

    QSlider *slider4 = new QSlider(Qt::Horizontal);
    slider4->setParent(this);
    slider4->setGeometry(10, 70, 400, 20);
    slider4->setRange(0, 100);
    slider4->setValue(100);

    QPushButton *btn1 = new QPushButton("1");
    btn1->setGeometry(10, 90, 100, 20);
    btn1->setParent(this);

    QPushButton *btn2 = new QPushButton("2");
    btn2->setGeometry(10, 110, 100, 20);
    btn2->setParent(this);

    QPushButton *btn3 = new QPushButton("exp");
    btn3->setGeometry(210, 90, 100, 20);
    btn3->setParent(this);

    QPushButton *btn4 = new QPushButton("col");
    btn4->setGeometry(210, 110, 100, 20);
    btn4->setParent(this);

    connect(slider1, SIGNAL(valueChanged(int)), this, SLOT(slider1Changed(int)));
    connect(slider2, SIGNAL(valueChanged(int)), this, SLOT(slider2Changed(int)));
    connect(slider3, SIGNAL(valueChanged(int)), this, SLOT(slider3Changed(int)));
    connect(slider4, SIGNAL(valueChanged(int)), this, SLOT(slider4Changed(int)));
    connect(btn1, SIGNAL(pressed()), this, SLOT(button1Pressed()));
    connect(btn2, SIGNAL(pressed()), this, SLOT(button2Pressed()));
    connect(btn3, SIGNAL(pressed()), this, SLOT(button3Pressed()));
    connect(btn4, SIGNAL(pressed()), this, SLOT(button4Pressed()));

    /-
    QWidget *widget = new QWidget;
    Ui::FloatingActionButtonSettingsForm *ui = new Ui::FloatingActionButtonSettingsForm;
    ui->setupUi(widget);

    setCentralWidget(widget);

    QtMaterialFloatingActionButton *fab = new QtMaterialFloatingActionButton(QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
    fab->setParent(this);
    -/

//    QWidget *widget = new QWidget;
//    QVBoxLayout *layout = new QVBoxLayout;
//
//    //QSizePolicy p(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
//    //widget->setSizePolicy(p);
//
//    layout->setContentsMargins(50, 0, 50, 0);
//    layout->setSizeConstraint(QLayout::SetMaximumSize);
//    layout->setSpacing(20);
//
//    widget->setLayout(layout);
//
//    layout->addStretch(1);
//
//    QtMaterialFlatButton *b = new QtMaterialFlatButton;
//    b->setText("Hello olleh");
//    b->setMaximumWidth(300);
//    layout->addWidget(b);
//
//    //b = new QtMaterialFlatButton;
//    //b->setText("Hello olleh");
//    //layout->addWidget(b);
//
//    setCentralWidget(widget);
//
//    // -------------------------------------------
//
//    QWidget *w = new QWidget;
//    QVBoxLayout *l = new QVBoxLayout;
//    w->setLayout(l);
//
//    QCheckBox *cb;
//    QComboBox *combo;
//    QLineEdit *le;
//    QHBoxLayout *hl;
//
//    cb = new QCheckBox;
//    cb->setText("Disabled");
//    l->addWidget(cb);
//
//    cb = new QCheckBox;
//    cb->setText("Show halo");
//    cb->setChecked(true);
//    l->addWidget(cb);
//
//    cb = new QCheckBox;
//    cb->setText("Transparent background");
//    cb->setChecked(true);
//    l->addWidget(cb);
//
//    hl = new QHBoxLayout;
//
//    QLabel *lbl = new QLabel("Role");
//    hl->addWidget(lbl);
//
//    combo = new QComboBox;
//    combo->addItem("Default");
//    combo->addItem("Primary");
//    combo->addItem("Secondary");
//    hl->addWidget(combo);
//    hl->setStretchFactor(combo, 2);
//
//    l->addLayout(hl);
//
//    // -------------------------------------------
//
//    layout->addWidget(w);
//    layout->addStretch(1);
//
//    return;
//
//
//    FlatButton *fbtn;
//
//    fbtn = new FlatButton("Call HQ");
////    fbtn->setMinimumHeight(42);
////    fbtn->setIcon(QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
////    fbtn->setIconSize(QSize(32, 32));
//    fbtn->setCheckable(true);
//    fbtn->setChecked(false);
//    fbtn->setShowHalo(false);
//    fbtn->setPeakOpacity(0.3);
//    layout->addWidget(fbtn);
//
//    QtMaterialFlatButton *qfbtn;
//
//    qfbtn = new QtMaterialFlatButton("Call HQ");
//    //qfbtn->setCheckable(true);
//    //qfbtn->setChecked(false);
//    //qfbtn->setShowHalo(false);
//    //qfbtn->setPeakOpacity(0.3);
//    layout->addWidget(qfbtn);
//
//
////    QPushButton *btn;
////
////    btn = new QPushButton("button 1");
////    layout->addWidget(btn);
////
////    btn = new QPushButton("button 2");
////    layout->addWidget(btn);
////
////    btn = new QPushButton("button 3");
////    layout->addWidget(btn);
////
////    QPushButton *fbtn;
////
////    fbtn = new FlatButton("Call HQ");
////    fbtn->setMinimumHeight(42);
////    fbtn->setIcon(QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
////    fbtn->setIconSize(QSize(32, 32));
////    layout->addWidget(fbtn);
////
////    fbtn = new FlatButton("button 2");
////    layout->addWidget(fbtn);
////
////    fbtn = new FlatButton("button 3");
////    layout->addWidget(fbtn);
//
//    widget->setParent(this);
//
////    _initMenu();
//
//    //AppMenu *am = new AppMenu;
//    //layout->addWidget(am);
//
////    Menu *m = new Menu;
////    m->addMenuItem("Item 1");
////    m->addMenuItem("Item 2");
////    m->addMenuItem("Item 3");
////
////    //layout->addWidget(m);
////
////    QPushButton *bt = new QPushButton("Helelele");
////
////    SizeProxyWidget *sp = new SizeProxyWidget(m);
////    layout->addWidget(sp);
////
////    QPushButton *bt2 = new QPushButton("Keso");
////    layout->addWidget(bt2);
//
//
//    /*
//
//    QVBoxLayout *layout = new QVBoxLayout;
//    QWidget *widget = new QWidget;
//
//    widget->setLayout(layout);
//    setCentralWidget(widget);
//
//    QPushButton *button = new QPushButton;
//    button->setText("Hello");
//    layout->addWidget(button);
//
//    Menu *menu = new Menu;
//    menu->addMenuItem("Menu item #1");
//    menu->addMenuItem("Menu item #2");
//    menu->addMenuItem("Menu item #3");
//
//    //menu->setParent(widget);
//
//    SizeProxy *proxy = new SizeProxy(menu);
//    QWidget *widget2 = new QWidget;
//    widget2->setLayout(proxy);
//    widget2->setParent(widget);
//
////    QPushButton *b = new QPushButton;
//
//    //TransparencyProxy *proxy = new TransparencyProxy;
//    //proxy->setWidget(menu);
//    ////layout->addWidget(proxy);
//
//    //QWidget *widget2 = new QWidget;
//    //widget2->setLayout(proxy);
//
//    //widget2->setParent(this);
//
//    return;
//    */
//
////    FlatButton *button = new FlatButton;
////    button->setText("Hello");
////
////    layout->addWidget(button);
//
//    /*
//    RaisedButton *button;
//
//    //RaisedButton btn2(*button);
//
//    button = new RaisedButton;
//    button->setText("Hello");
//
//    layout->addWidget(button);
//
//    //
//
//    Menu *menu = new Menu;
//    menu->addMenuItem("Menu item #1");
//    menu->addMenuItem("Menu item #2");
//    menu->addMenuItem("Menu item #3");
//
//    layout->addWidget(menu);
//
//    //
//
//    Drawer *drawer = new Drawer;
//
//    connect(button, SIGNAL(clicked(bool)), drawer, SLOT(openDrawer()));
//
//    drawer->setParent(this);
//
//    QPushButton *btn1 = new QPushButton;
//    btn1->setText("Hello");
//
//    connect(btn1, SIGNAL(clicked(bool)), drawer, SLOT(openDrawer()));
//
//    QPushButton *btn2 = new QPushButton;
//    btn2->setText("This is a button");
//
//    connect(btn2, SIGNAL(clicked(bool)), drawer, SLOT(closeDrawer()));
//
//    layout = new QVBoxLayout;
//    layout->addWidget(btn1);
//    layout->addWidget(btn2);
//    layout->addStretch();
//
//    drawer->setDrawerLayout(layout);
//
//    //TestRippleOverlay *overlay = new TestRippleOverlay;
//    //overlay->setParent(this);
//    */
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.setPen(Qt::green);

    painter.drawRect(rect());
}

void MainWindow::_initMenu() const
{
    QMenu *file = new QMenu("&File");

    //QAction *exitAction = file->addAction("E&xit");

    AppMenu *components = new AppMenu("&Components");
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

void MainWindow::slider1Changed(int value)
{
    //_menu->_proxy->setXScale(static_cast<qreal>(value)/100);
}

void MainWindow::slider2Changed(int value)
{
    //_menu->_proxy->setYScale(static_cast<qreal>(value)/100);
}

void MainWindow::slider3Changed(int value)
{
//    _menu->_proxy->setCanvasXScale(static_cast<qreal>(value)/100);
}

void MainWindow::slider4Changed(int value)
{
//    _menu->_proxy->setCanvasYScale(static_cast<qreal>(value)/100);
}

void MainWindow::button1Pressed()
{
    QStackedLayout *sl = static_cast<QStackedLayout *>(_menu->layout());
    sl->setCurrentIndex(0);
}

void MainWindow::button2Pressed()
{
    QStackedLayout *sl = static_cast<QStackedLayout *>(_menu->layout());
    sl->setCurrentIndex(1);
}

void MainWindow::button3Pressed()
{
    _menu->expand();
}

void MainWindow::button4Pressed()
{
    _menu->collapse();
}
