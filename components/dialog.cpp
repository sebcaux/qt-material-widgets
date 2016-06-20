#include "dialog.h"
#include "dialog_p.h"
#include <QPainter>
#include <QEvent>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include "lib/transparencyproxy.h"
#include "dialog_internal.h"

DialogPrivate::DialogPrivate(Dialog *q)
    : q_ptr(q)
{
}

void DialogPrivate::init()
{
    Q_Q(Dialog);

    QVBoxLayout *layout = new QVBoxLayout;
    q->setLayout(layout);

    QWidget *widget = new QWidget;

    proxy = new TransparencyProxy;
    widget->setLayout(proxy);
    layout->addWidget(widget);
    layout->setAlignment(widget, Qt::AlignCenter);

    widget->setMinimumWidth(400);
    widget->setMinimumHeight(400);

    window = new DialogWindow(q);
    proxy->setWidget(window);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setColor(QColor(0, 0, 0, 200));
    effect->setBlurRadius(64);
    effect->setOffset(0, 13);
    widget->setGraphicsEffect(effect);

/*
    {
        QVBoxLayout *layout = new QVBoxLayout;
        window->setLayout(layout);

        QPushButton *button = new QPushButton;
        button->setText("Hello test!");
        layout->addWidget(button);

        button = new QPushButton;
        button->setText("Hello test!");
        layout->addWidget(button);

        button = new QPushButton;
        button->setText("Hello test!");
        layout->addWidget(button);

        button = new QPushButton;
        button->setText("Hello test!");
        layout->addWidget(button);

        button = new QPushButton;
        button->setText("Hello test!");
        layout->addWidget(button);
    }
    */

    //

    proxy->setCurrentIndex(1);

    //



    QPushButton *btn;

    btn = new QPushButton;
    btn->setText("One");
    layout->addWidget(btn);

    QObject::connect(btn, SIGNAL(pressed()), q, SLOT(pressOne()));

    btn = new QPushButton;
    btn->setText("Two");
    layout->addWidget(btn);

    QObject::connect(btn, SIGNAL(pressed()), q, SLOT(pressTwo()));
}

Dialog::Dialog(QWidget *parent)
    : QWidget(parent),
      d_ptr(new DialogPrivate(this))
{
    d_func()->init();
}

Dialog::~Dialog()
{
}

QLayout *Dialog::windowLayout() const
{
    Q_D(const Dialog);

    return d->window->layout();
}

void Dialog::setWindowLayout(QLayout *layout)
{
    Q_D(Dialog);

    d->window->setLayout(layout);
}

void Dialog::pressOne()
{
    Q_D(Dialog);

    d->proxy->setOpaque();
}

void Dialog::pressTwo()
{
    Q_D(Dialog);

    d->proxy->setOpacity(0.5);
}

bool Dialog::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::ParentChange:
    {
        if (!parent())
            break;

        parent()->installEventFilter(this);

        QWidget *widget;
        if ((widget = parentWidget())) {
            setGeometry(widget->rect());
        }
        break;
    }
    case QEvent::ParentAboutToChange:
    {
        if (!parent())
            break;

        parent()->removeEventFilter(this);
        break;
    }
    default:
        break;
    }
    return QWidget::event(event);
}

bool Dialog::eventFilter(QObject *obj, QEvent *event)
{
    QEvent::Type type = event->type();

    if (QEvent::Move == type || QEvent::Resize == type)
    {
        QWidget *widget;
        if ((widget = parentWidget())) {
            setGeometry(widget->rect());
        }
    }
    return QWidget::eventFilter(obj, event);
}

void Dialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    //QPen pen;
    //pen.setColor(Qt::blue);
    //pen.setWidth(3);
    //painter.setPen(pen);

    //painter.drawRect(rect());

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.setOpacity(0.5);

    painter.drawRect(rect());
}

//#include "dialog.h"
//#include "dialog_p.h"
//#include <QEvent>
//#include <QPainter>
//#include <QGraphicsDropShadowEffect>
//#include <QGraphicsBlurEffect>
//#include <QGraphicsOpacityEffect>
//#include <QVBoxLayout>
//#include <QStackedLayout>
//#include <QPushButton>
//#include "lib/customshadoweffect.h"
//#include "dialog_internal.h"
//
//DialogPrivate::DialogPrivate(Dialog *q)
//    : q_ptr(q)
////      window(new DialogWindow(q)),
////      shadow(new DialogShadow(q))
//{
//}
//
//void DialogPrivate::init()
//{
//    Q_Q(Dialog);
//
//    QVBoxLayout *l = new QVBoxLayout;
//
//    layout = new QStackedLayout;
//    l->addLayout(layout);
//
//    QPushButton *button = new QPushButton;
//    button->setText("Hello test!");
//    layout->addWidget(button);
//
//    proxy = new DialogProxy(q, button);
//    layout->addWidget(proxy);
//
//    //q->setLayout(layout);
//    q->setLayout(l);
//
//    layout->setCurrentIndex(1);
//
//    button = new QPushButton;
//    button->setText("one");
//    l->addWidget(button);
//
//    QObject::connect(button, SIGNAL(pressed()), q, SLOT(pressOne()));
//
//    button = new QPushButton;
//    button->setText("two");
//    l->addWidget(button);
//
//    QObject::connect(button, SIGNAL(pressed()), q, SLOT(pressTwo()));
//
//    /*
//
//    return;
//
//    QVBoxLayout *layout = new QVBoxLayout;
//
//    dialogWidget = new QWidget;
//    dialogWidget->setLayout(layout);
//
//    //q->setLayout(layout);
//
//    layout->addWidget(window);
//    layout->setAlignment(window, Qt::AlignCenter);
//
//    window->setMinimumWidth(500);
//    window->setMinimumHeight(500);
//
//    shadow->setWindow(window);
//
//    //window->setAttribute(Qt::WA_DontShowOnScreen);
//
//    //QSizePolicy sp = window->sizePolicy();
//    //sp.setRetainSizeWhenHidden(true);
//    //window->setSizePolicy(sp);
//
//    //window->setHidden(true);
//
//    //CustomShadowEffect *fx = new CustomShadowEffect;
//    //fx->setBlurRadius(8);
//    //fx->setColor(Qt::black);
//
//    //window->setGraphicsEffect(fx);
//
//    //QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect;
//    //opacity->setOpacity(1);
//    //q->setGraphicsEffect(opacity);
//
//    //QGraphicsBlurEffect *blur = new QGraphicsBlurEffect;
//    //blur->setBlurRadius(32);
//    //shadow->setGraphicsEffect(blur);
//
//    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
//    effect->setColor(QColor(0, 0, 0, 200));
//    effect->setBlurRadius(64);
//    effect->setOffset(0, 13);
//    window->setGraphicsEffect(effect);
//
//    //    QVBoxLayout *layout = new QVBoxLayout;
//    //    window->setLayout(layout);
//
////        QPushButton *button = new QPushButton;
////        button->setText("Hello test!");
////        layout->addWidget(button);
////
////        button = new QPushButton;
////        button->setText("Hello test!");
////        layout->addWidget(button);
////
////        button = new QPushButton;
////        button->setText("Hello test!");
////        layout->addWidget(button);
////
////        button = new QPushButton;
////        button->setText("Hello test!");
////        layout->addWidget(button);
////
////        button = new QPushButton;
////        button->setText("Hello test!");
////        layout->addWidget(button);
//
//    //window->setGeometry(0, 0, 500, 500);
//    window->setFixedSize(500, 500);
//
//    */
//}
//
//Dialog::Dialog(QWidget *parent)
//    : QWidget(parent),
//      d_ptr(new DialogPrivate(this))
//{
//    d_func()->init();
//}
//
//Dialog::~Dialog()
//{
//}
//
//void Dialog::pressOne()
//{
//    Q_D(Dialog);
//
//    d->layout->setCurrentIndex(0);
//}
//
//void Dialog::pressTwo()
//{
//    Q_D(Dialog);
//
//    d->layout->setCurrentIndex(1);
//}
//
////QWidget *Dialog::dialogWidget() const
////{
////    Q_D(const Dialog);
////
////    return d->dialogWidget;
////}
//
///*
//bool Dialog::event(QEvent *event)
//{
//    Q_D(Dialog);
//
//    switch (event->type())
//    {
//    case QEvent::ParentChange:
//    {
//        if (!parent())
//            break;
//
//        parent()->installEventFilter(this);
//
//        QWidget *widget;
//        if ((widget = parentWidget())) {
//            d->window->setParent(parentWidget());
//            setGeometry(widget->rect());
//        }
//        break;
//    }
//    case QEvent::ParentAboutToChange:
//    {
//        if (!parent())
//            break;
//
//        parent()->removeEventFilter(this);
//        break;
//    }
//    default:
//        break;
//    }
//    return QWidget::event(event);
//}
//
//bool Dialog::eventFilter(QObject *obj, QEvent *event)
//{
//    QEvent::Type type = event->type();
//
//    if (QEvent::Move == type || QEvent::Resize == type)
//    {
//        QWidget *widget;
//        if ((widget = parentWidget())) {
//            setGeometry(widget->rect());
//        }
//    }
//    return QWidget::eventFilter(obj, event);
//}
//*/
//
//void Dialog::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event)
//
//    QPainter painter(this);
//
//    QBrush brush;
//    brush.setStyle(Qt::SolidPattern);
//    brush.setColor(Qt::black);
//    painter.setBrush(brush);
//    painter.setPen(Qt::NoPen);
//
//    painter.setOpacity(0.5);
//
//    painter.drawRect(rect());
//
//    //QPainter painter(this);
//
//    //QPen pen;
//    //pen.setWidth(12);
//    //painter.setPen(pen);
//
//    //painter.drawRect(rect());
//}
//
