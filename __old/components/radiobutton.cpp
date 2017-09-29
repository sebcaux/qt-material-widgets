#include "radiobutton.h"
#include "radiobutton_p.h"
#include <QStateMachine>
#include <QEvent>
#include <QSignalTransition>
#include <QEventTransition>
#include <QPropertyAnimation>
#include <QApplication>
#include <QDebug>

RadioButtonPrivate::RadioButtonPrivate(RadioButton *q)
    : CheckablePrivate(q)
{
}

RadioButtonPrivate::~RadioButtonPrivate()
{
}

void RadioButtonPrivate::init()
{
    Q_Q(RadioButton);

    q->setAutoExclusive(true);

    q->setCheckedIcon(QIcon("../qt-material-widgets/ic_radio_button_checked_black_24px.svg"));
    q->setUncheckedIcon(QIcon("../qt-material-widgets/ic_radio_button_unchecked_black_24px.svg"));

    uncheckedState->assignProperty(checkedIcon, "iconSize", 0);
    uncheckedState->assignProperty(uncheckedIcon, "iconSize", 24);
    disabledUncheckedState->assignProperty(checkedIcon, "iconSize", 0);
    disabledUncheckedState->assignProperty(uncheckedIcon, "iconSize", 24);

    checkedState->assignProperty(uncheckedIcon, "iconSize", 0);
    checkedState->assignProperty(checkedIcon, "iconSize", 24);
    disabledCheckedState->assignProperty(uncheckedIcon, "iconSize", 0);
    disabledCheckedState->assignProperty(checkedIcon, "iconSize", 24);

    uncheckedState->assignProperty(checkedIcon, "opacity", 0);
    uncheckedState->assignProperty(uncheckedIcon, "opacity", 1);
    checkedState->assignProperty(uncheckedIcon, "opacity", 0);
    checkedState->assignProperty(checkedIcon, "opacity", 1);

    disabledUncheckedState->assignProperty(uncheckedIcon, "opacity", 1);
    disabledCheckedState->assignProperty(checkedIcon, "opacity", 1);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(checkedIcon, "iconSize", q);
    animation->setDuration(250);
    machine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "iconSize", q);
    animation->setDuration(250);
    machine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "opacity", q);
    animation->setDuration(250);
    machine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(checkedIcon, "opacity", q);
    animation->setDuration(250);
    machine->addDefaultAnimation(animation);
}

RadioButton::RadioButton(QWidget *parent)
    : Checkable(*new RadioButtonPrivate(this), parent)
{
    Q_D(RadioButton);

    d->init();

    RadioButton::assignProperties();

    d->machine->start();
    QCoreApplication::processEvents();
}

RadioButton::~RadioButton()
{
}

void RadioButton::assignProperties()
{
    Q_D(RadioButton);

    d->disabledUncheckedState->assignProperty(d->uncheckedIcon, "color", disabledColor());
    d->disabledUncheckedState->assignProperty(d->checkedIcon, "color", disabledColor());
    d->disabledCheckedState->assignProperty(d->checkedIcon, "color", disabledColor());
    d->disabledCheckedState->assignProperty(d->uncheckedIcon, "color", disabledColor());

    d->uncheckedState->assignProperty(d->uncheckedIcon, "color", uncheckedColor());
    d->uncheckedState->assignProperty(d->checkedIcon, "color", checkedColor());
    d->checkedState->assignProperty(d->uncheckedIcon, "color", uncheckedColor());
    d->checkedState->assignProperty(d->checkedIcon, "color", checkedColor());
}
