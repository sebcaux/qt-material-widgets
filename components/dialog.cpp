#include "dialog.h"
#include "dialog_p.h"
#include <QPainter>
#include <QApplication>
#include <QStateMachine>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QEvent>
#include <QMouseEvent>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include "lib/transparencyproxy.h"
#include "dialog_internal.h"
#include <QDebug>

DialogPrivate::DialogPrivate(Dialog *q)
    : q_ptr(q),
      machine(new QStateMachine(q)),
      window(new DialogWindow(q)),
      proxy(new TransparencyProxy)
{
}

void DialogPrivate::init()
{
    Q_Q(Dialog);

    QVBoxLayout *layout = new QVBoxLayout;
    q->setLayout(layout);

    q->setAttribute(Qt::WA_TransparentForMouseEvents);

    QWidget *widget = new QWidget;

    widget->setLayout(proxy);
    layout->addWidget(widget);
    layout->setAlignment(widget, Qt::AlignCenter);

    widget->setMinimumWidth(400);

    proxy->setWidget(window);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setColor(QColor(0, 0, 0, 200));
    effect->setBlurRadius(64);
    effect->setOffset(0, 13);
    widget->setGraphicsEffect(effect);

    //

    QState *hiddenState = new QState;
    QState *visibleState = new QState;

    machine->addState(hiddenState);
    machine->addState(visibleState);

    machine->setInitialState(hiddenState);

    QSignalTransition *transition;

    transition = new QSignalTransition(window, SIGNAL(dialogActivated()));
    transition->setTargetState(visibleState);
    hiddenState->addTransition(transition);

    transition = new QSignalTransition(window, SIGNAL(dialogDeactivated()));
    transition->setTargetState(hiddenState);
    visibleState->addTransition(transition);

    visibleState->assignProperty(proxy, "opacity", 1);
    visibleState->assignProperty(effect, "color", QColor(0, 0, 0, 200));
    visibleState->assignProperty(window, "offset", 0);
    hiddenState->assignProperty(proxy, "opacity", 0);
    hiddenState->assignProperty(effect, "color", QColor(0, 0, 0, 0));
    hiddenState->assignProperty(window, "offset", 200);

    QObject::connect(proxy, SIGNAL(opacityChanged()), q, SLOT(update()));

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(proxy, "opacity", q);
    animation->setDuration(280);
    machine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(effect, "color", q);
    animation->setDuration(280);
    machine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(window, "offset", q);
    animation->setDuration(280);
    animation->setEasingCurve(QEasingCurve::OutCirc);
    machine->addDefaultAnimation(animation);

    QObject::connect(visibleState, SIGNAL(propertiesAssigned()), q, SLOT(acceptMouseEvents()));

    machine->start();

    QCoreApplication::processEvents();
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

void Dialog::showDialog()
{
    Q_D(Dialog);

    emit d->window->dialogActivated();
}

void Dialog::hideDialog()
{
    Q_D(Dialog);

    emit d->window->dialogDeactivated();
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void Dialog::acceptMouseEvents()
{
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
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

void Dialog::mousePressEvent(QMouseEvent *event)
{
    Q_D(Dialog);

    QRect rect(d->window->mapToGlobal(QPoint(0, 0)), d->window->size());
    if (!rect.contains(event->globalPos())) {
        hideDialog();
    }
}

void Dialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(Dialog);

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.setOpacity(d->proxy->opacity()/2);

    painter.drawRect(rect());
}
