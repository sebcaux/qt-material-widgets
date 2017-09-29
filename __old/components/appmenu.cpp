#include "appmenu.h"
#include <QPainter>
#include <QAction>
#include <QActionEvent>
#include <QDebug>
#include <QLayout>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QGraphicsDropShadowEffect>
#include "components/flatbutton.h"
#include "lib/sizeproxywidget.h"
#include "components/menu.h"

AppMenu::AppMenu(QWidget *parent)
    : QMenu(parent),
      _menu(new Menu),
      _proxyWidget(new SizeProxyWidget(_menu))
{
    init();

    ////SizeProxy *proxy = new SizeProxy(new QPushButton("XX"));
    //_proxy = new SizeProxy(_menu);
    //setLayout(_proxy);

    //_proxy->setScale(0.5, 0.5);

    ////_menu->setVisible(false);
    //_menu->installEventFilter(this);

    //setMinimumSize(1, 1);

    //setLayout(new QVBoxLayout);
    //layout()->setSpacing(0);
    //layout()->setContentsMargins(0, 0, 0, 0);
}

AppMenu::AppMenu(const QString &title, QWidget *parent)
    : QMenu(title, parent),
      _menu(new Menu),
      _proxyWidget(new SizeProxyWidget(_menu))
{
    init();

    ////SizeProxy *proxy = new SizeProxy(new QPushButton("XX"));
    //_proxy = new SizeProxy(_menu);
    //setLayout(_proxy);

    //_proxy->setScale(0.5, 0.5);

    ////_menu->setVisible(false);
    //_menu->installEventFilter(this);

    //setMinimumSize(1, 1);

    //QVBoxLayout *l = new QVBoxLayout;
    //l->addWidget(_menu);
    //setLayout(l);

    //SizeProxy *proxy = new SizeProxy(this);
    //setLayout(proxy);

    //setLayout(new QVBoxLayout);
    //layout()->setSpacing(0);
    //layout()->setContentsMargins(0, 0, 0, 0);
}

AppMenu::~AppMenu()
{
}

void AppMenu::animateExpand()
{
    QParallelAnimationGroup *group;
    group = new QParallelAnimationGroup;

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation;
    animation->setTargetObject(_proxyWidget);
    animation->setPropertyName("canvasXScale");
    animation->setStartValue(0.5);
    animation->setEndValue(1);
    animation->setDuration(1350);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    group->addAnimation(animation);

    animation = new QPropertyAnimation;
    animation->setTargetObject(_proxyWidget);
    animation->setPropertyName("canvasYScale");
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setDuration(1350);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    group->addAnimation(animation);

    animation = new QPropertyAnimation;
    animation->setTargetObject(_proxyWidget);
    animation->setPropertyName("xScale");
    animation->setStartValue(0.55);
    animation->setEndValue(1);
    animation->setDuration(1700);
    animation->setEasingCurve(QEasingCurve::OutBounce);
    group->addAnimation(animation);

    animation = new QPropertyAnimation;
    animation->setTargetObject(_proxyWidget);
    animation->setPropertyName("yScale");
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setDuration(1700);
    animation->setEasingCurve(QEasingCurve::OutBounce);
    group->addAnimation(animation);

    animation = new QPropertyAnimation;
    animation->setTargetObject(_proxyWidget);
    animation->setPropertyName("opacity");
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setDuration(1600);
    group->addAnimation(animation);

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

//bool AppMenu::event(QEvent *event)
//{
//    switch (event->type())
//    {
//    case QEvent::Resize:
//    case QEvent::Move: {
//        /*
//        QList<QAction *>::const_iterator i;
//        for (i = actions().begin(); i != actions().end(); ++i) {
//            QAction *action = *i;
//            FlatButton *item = menuItems.value(action);
//            //item->setGeometry(actionGeometry(action));
//        }
//        */
//        break;
//    }
//    default:
//        break;
//    }
//    return QMenu::event(event);
//}

bool AppMenu::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::Resize == event->type()) {

        //setGeometry(_proxyWidget->geometry().translated(x(), y()));

        setGeometry(x(), y(), 400, 800);

        //setGeometry(_proxyWidget->sourceGeometry().translated(x(), y()));

        //QRect rect(_proxyWidget->sourceGeometry());

        //rect.translate(x(), y());

        //rect.setWidth(static_cast<qreal>(rect.width())*_proxyWidget->canvasXScale());
        //rect.setHeight(static_cast<qreal>(rect.height())*_proxyWidget->canvasYScale());

        //setGeometry(rect);

    }
    return QMenu::eventFilter(obj, event);
}

//void AppMenu::actionEvent(QActionEvent *event)
//{
//    switch (event->type())
//    {
//    case QEvent::ActionAdded:
//    {
//        break;
//
//        QAction *action = event->action();
//
//        _menu->addMenuItem(action->text());
//
//        /*
//        QAction *action = event->action();
//        FlatButton *button = new FlatButton;
//        button->setText(action->text());
//
//        QFont font(button->font());
//        font.setCapitalization(QFont::MixedCase);
//        font.setPointSize(11);
//        font.setStyleName("Regular");
//        button->setFont(font);
//        button->setMinimumHeight(48);
//        button->setShowHalo(false);
//        button->setParent(this);
//        button->setIcon(QIcon("../qt-material-widgets/face.svg"));
//        menuItems.insert(action, button);
//        layout()->addWidget(button);
//        */
//        break;
//    }
//    case QEvent::ActionRemoved: {
//        break;
//    }
//    case QEvent::ActionChanged: {
//        break;
//    }
//    default:
//        break;
//    }
//    QMenu::actionEvent(event);
//}
//
//void AppMenu::mouseMoveEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event)
//}

void AppMenu::actionEvent(QActionEvent *event)
{
    switch (event->type())
    {
    case QEvent::ActionAdded:
    {
        QAction *action = event->action();
        _menu->addMenuItem(action->text());
        break;
    }
    case QEvent::ActionRemoved:
    {
        break;
    }
    case QEvent::ActionChanged:
    {
        break;
    }
    default:
        break;
    }
    QMenu::actionEvent(event);
}

void AppMenu::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    QMenu::mousePressEvent(event);
}

void AppMenu::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    //painter.drawRect(rect());

    //QBrush brush;
    //brush.setStyle(Qt::SolidPattern);
    //brush.setColor(Qt::white);
    //painter.setOpacity(1.0);
    //painter.setBrush(brush);
    //painter.setPen(Qt::NoPen);
    //painter.drawRect(rect());

    //painter.drawRect(_proxyWidget->sourceGeometry());
    //painter.drawRect(rect());

    //rect.setWidth(static_cast<qreal>(rect.width())*_proxyWidget->canvasXScale());
    //rect.setHeight(static_cast<qreal>(rect.height())*_proxyWidget->canvasYScale());


//    QPen pen;
//    pen.setColor(Qt::red);
//    pen.setWidth(3);
//    painter.setPen(pen);
//    painter.setBrush(Qt::NoBrush);
//
//    //QRect r(rect());
//    //r.setWidth(static_cast<qreal>(r.width())*_proxyWidget->xScale());
//
//    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    //QMenu::paintEvent(event);

//    QMenu::paintEvent(event);

    //QMenu::paintEvent(event);
//    QList<QAction *> items = actions();

//    if (!items.isEmpty())
//    {
//        qreal h = static_cast<qreal>(height())/items.length();
//
//        int c = 0;
//        QList<QAction *>::const_iterator i;
//        for (i = items.begin(); i != items.end(); ++i) {
//
//            //cqDebug() << actionGeometry(*i);
//
//            painter.drawRect(0, h*c++, width(), h);
//        }
//    }
}

void AppMenu::init()
{
    //_menu->addMenuItem("adsfdsfadf");
    //_menu->addMenuItem("bdsfdsfadf");
    //_menu->addMenuItem("cdsfdsfadf");


//    _proxyWidget->show();
    //_proxyWidget->setParent(this);
    //_proxyWidget->setWindowFlags(Qt::Widget);
    //_proxyWidget->setAutoFillBackground(false);
    //_proxyWidget->setAttribute( Qt::WA_TranslucentBackground, true );
    //_proxyWidget->setAttribute(Qt::WA_NoSystemBackground);
    //_proxyWidget->setAttribute( Qt::WA_OpaquePaintEvent, false);

    //QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    //effect->setColor(QColor(0, 0, 0));
    //effect->setOffset(0, 1);
    //effect->setBlurRadius(16);

    //_proxyWidget->setGraphicsEffect(effect);

    //setAutoFillBackground(true);

    //setPalette(Qt::transparent);
    //setAutoFillBackground(false);
    //setAttribute(Qt::WA_NoSystemBackground);

    setStyleSheet("QMenu { background-color: transparent; }");

    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(_proxyWidget);
    l->setSizeConstraint(QLayout::SetMaximumSize);
    l->setContentsMargins(0, 0, 0, 0);
    setLayout(l);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setColor(QColor(0, 0, 0));
    effect->setOffset(0, 1);
    effect->setBlurRadius(16);

    _proxyWidget->setGraphicsEffect(effect);

    //_proxyWidget->setXScale(1.0);
    //_proxyWidget->setXScale(0.5);
    //_proxyWidget->setYScale(1.0);

    connect(this, SIGNAL(aboutToShow()), this, SLOT(animateExpand()));

    _proxyWidget->installEventFilter(this);

    //_menu->installEventFilter(this);

    //setAttribute(Qt::WA_NoSystemBackground);
//    setAttribute(Qt::WA_NoSystemBackground);
    //_proxyWidget->setWindowFlags(_proxyWidget->windowFlags() | Qt::FramelessWindowHint);
    //setAutoFillBackground(false);

    //setWindowFlags(windowFlags());


    //setAutoFillBackground(false);

   // _proxyWidget->setAttribute(Qt::WA_OpaquePaintEvent);

    //setMinimumSize(10, 10);
}
