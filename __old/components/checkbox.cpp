#include "checkbox.h"
#include "checkbox_p.h"
#include <QStateMachine>
#include <QEvent>
#include <QSignalTransition>
#include <QEventTransition>
#include <QPropertyAnimation>
#include <QApplication>
#include <QDebug>

CheckBoxPrivate::CheckBoxPrivate(CheckBox *q)
    : CheckablePrivate(q)
{
}

CheckBoxPrivate::~CheckBoxPrivate()
{
}

void CheckBoxPrivate::init()
{
    Q_Q(CheckBox);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(checkedIcon, "iconSize", q);
    animation->setStartValue(0);
    animation->setEndValue(24);
    animation->setDuration(280);
    //animation->setDuration(6250);
    uncheckedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "color", q);
    animation->setDuration(250);
    uncheckedTransition->addAnimation(animation);

    //

    animation = new QPropertyAnimation(uncheckedIcon, "color", q);
    animation->setDuration(1550);
    checkedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(checkedIcon, "opacity", q);
    animation->setDuration(650);
    checkedTransition->addAnimation(animation);

    //

    checkedState->assignProperty(checkedIcon, "iconSize", 24);
    checkedState->assignProperty(checkedIcon, "opacity", 1);
    checkedState->assignProperty(uncheckedIcon, "opacity", 0);

    uncheckedState->assignProperty(checkedIcon, "opacity", 0);
    uncheckedState->assignProperty(uncheckedIcon, "opacity", 1);

    disabledCheckedState->assignProperty(checkedIcon, "opacity", 1);
    disabledUncheckedState->assignProperty(uncheckedIcon, "opacity", 1);
}

CheckBox::CheckBox(QWidget *parent)
    : Checkable(*new CheckBoxPrivate(this), parent)
{
    Q_D(CheckBox);

    d->init();

    CheckBox::assignProperties();

    d->machine->start();
    QCoreApplication::processEvents();
}

CheckBox::~CheckBox()
{
}

void CheckBox::assignProperties()
{
    Q_D(CheckBox);

    d->checkedState->assignProperty(d->checkedIcon, "color", checkedColor());
    d->checkedState->assignProperty(d->uncheckedIcon, "color", checkedColor());
    d->uncheckedState->assignProperty(d->uncheckedIcon, "color", uncheckedColor());
    d->uncheckedState->assignProperty(d->uncheckedIcon, "color", uncheckedColor());
    d->disabledUncheckedState->assignProperty(d->uncheckedIcon, "color", disabledColor());
    d->disabledCheckedState->assignProperty(d->checkedIcon, "color", disabledColor());
}
