#include "menuplus.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QGraphicsDropShadowEffect>
#include <QEvent>
#include <QPainter>
#include <QStateMachine>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QTimer>
//#include "components/menuitemplus.h"
#include "xx/qtmaterialmenuitem.h"
#include "components/scrollwidget.h"
#include "components/menuplusproxy.h"

#include "xx/qtmaterialflatbutton.h"
#include <QDebug>

#include "xxlib/qtmaterialoverlaywidget.h"

MenuPlus::MenuPlus(QWidget *parent)
    : QWidget(parent),
      _layout(new QStackedLayout),
      _widget(new QWidget),
      _scrollBar(new ScrollBar),
      _effect(new QGraphicsDropShadowEffect),
      _proxy(new MenuPlusProxy(_widget, _effect)),
      _stateMachine(new QStateMachine(this))
{
    QScrollArea *area = new QScrollArea;
    _layout->addWidget(area);
    setLayout(_layout);
    _layout->setSpacing(0);
    _layout->setMargin(0);

    QVBoxLayout *l = new QVBoxLayout;
    l->setSpacing(0);
    l->setMargin(0);
    _widget->setLayout(l);

    area->setWidget(_widget);
    area->setWidgetResizable(true);
    area->setBackgroundRole(QPalette::Base);
    area->setAutoFillBackground(true);

    //

    _layout->addWidget(_proxy);

    //

    area->setVerticalScrollBar(_scrollBar);
    _scrollBar->setHideOnMouseOut(false);

    //

    area->setLineWidth(0);
    area->setMidLineWidth(0);
    area->setFrameShape(QFrame::NoFrame);
    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    _effect->setBlurRadius(9);
    _effect->setOffset(QPoint(0, 0));
    _effect->setColor(QColor(0, 0, 0, 100));
    setGraphicsEffect(_effect);

    //

    _layout->setCurrentIndex(1);

    QState *expandedState = new QState;
    QState *collapsedState = new QState;
    _stateMachine->addState(expandedState);
    _stateMachine->addState(collapsedState);
    //_stateMachine->setInitialState(expandedState);
    _stateMachine->setInitialState(collapsedState);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

    transition = new QSignalTransition(_proxy, SIGNAL(expand()));
    transition->setTargetState(expandedState);
    collapsedState->addTransition(transition);

    animation = new QPropertyAnimation(this);
    animation->setTargetObject(_proxy);
    animation->setPropertyName("xScale");
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    //animation->setEasingCurve(QEasingCurve::OutElastic);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this);
    animation->setTargetObject(_proxy);
    animation->setPropertyName("yScale");
    //animation->setDuration(900);
    animation->setDuration(400);
    //animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->setEasingCurve(QEasingCurve::OutElastic);
    //animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    transition = new QSignalTransition(_proxy, SIGNAL(collapse()));
    transition->setTargetState(collapsedState);
    expandedState->addTransition(transition);

    animation = new QPropertyAnimation(this);
    animation->setTargetObject(_proxy);
    animation->setPropertyName("xScale");
    animation->setDuration(400);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this);
    animation->setTargetObject(_proxy);
    animation->setPropertyName("yScale");
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    expandedState->assignProperty(_proxy, "xScale", 1);
    expandedState->assignProperty(_proxy, "yScale", 1);
    expandedState->assignProperty(_proxy, "opacity", 1);

    collapsedState->assignProperty(_proxy, "xScale", 0.5);
    //collapsedState->assignProperty(_proxy, "xScale", 1);
    collapsedState->assignProperty(_proxy, "yScale", 0.05);
    collapsedState->assignProperty(_proxy, "opacity", 0);

    animation = new QPropertyAnimation(this);
    animation->setTargetObject(_proxy);
    animation->setPropertyName("opacity");
    animation->setDuration(150);
    _stateMachine->addDefaultAnimation(animation);

    connect(expandedState, SIGNAL(propertiesAssigned()), this, SLOT(setOpaque()));
    connect(expandedState, SIGNAL(propertiesAssigned()), this, SIGNAL(wasExpanded()));
    connect(collapsedState, SIGNAL(propertiesAssigned()), this, SIGNAL(wasCollapsed()));

    _stateMachine->start();

    //

    QtMaterialMenuItem *b;

    b = new QtMaterialMenuItem;
    b->setText("Hello 123");
    l->addWidget(b);

    connect(b, SIGNAL(pressed()), this, SLOT(collapseDelayed()));

    b = new QtMaterialMenuItem;
    b->setText("Select everything");
    b->setIcon(QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Run something");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Download internet");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Done");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Run something");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Download internet");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Done");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Select everything");
    b->setIcon(QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Run something");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Download internet");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Done");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Run something");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Download internet");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Done");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Select everything");
    b->setIcon(QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Run something");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Download internet");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Done");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Run something");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Download internet");
    l->addWidget(b);

    b = new QtMaterialMenuItem;
    b->setText("Done");
    l->addWidget(b);
}

MenuPlus::~MenuPlus()
{
}

void MenuPlus::addMenuItem(const QString &text)
{
    Q_UNUSED(text)
}

void MenuPlus::collapse()
{
    _layout->setCurrentIndex(1);
    emit _proxy->collapse();
    emit aboutToCollapse();
}

void MenuPlus::collapseDelayed()
{
    QTimer::singleShot(200, this, SLOT(collapse()));
}

void MenuPlus::expand()
{
    _layout->setCurrentIndex(1);
    emit _proxy->expand();
    emit aboutToExpand();
}

void MenuPlus::setOpaque()
{
    _layout->setCurrentIndex(0);
}
