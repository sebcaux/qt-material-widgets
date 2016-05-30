#include "flatbutton_internal.h"
#include <QAbstractTransition>
#include <QEventTransition>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include "flatbutton.h"
#include "lib/style.h"

FlatButtonDelegate::FlatButtonDelegate(FlatButton *parent)
    : QStateMachine(parent),
      button(parent),
      _normalState(new QState(this)),
      _normalFocusedState(new QState(this)),
      _hoveredState(new QState(this)),
      _hoveredFocusedState(new QState(this)),
      _pressedState(new QState(this)),
      _focusHaloSize(0.8)
{
    setInitialState(_normalState);

    addTransition(QEvent::Enter, _normalFocusedState, _hoveredFocusedState);
    addTransition(QEvent::FocusIn, _normalState, _normalFocusedState);
    addTransition(QEvent::FocusOut, _normalFocusedState, _normalState);
    addTransition(QEvent::Enter, _normalState, _hoveredState);
    addTransition(QEvent::Leave, _hoveredFocusedState, _normalFocusedState);
    addTransition(QEvent::Leave, _hoveredState, _normalState);
    addTransition(QEvent::MouseButtonPress, _hoveredState, _pressedState);
    addTransition(QEvent::MouseButtonRelease, _pressedState, _hoveredFocusedState);

    QSequentialAnimationGroup *group = new QSequentialAnimationGroup(this);

    QPropertyAnimation *grow = new QPropertyAnimation;
    QPropertyAnimation *shrink = new QPropertyAnimation;

    grow->setTargetObject(this);
    grow->setPropertyName("focusHaloSize");
    grow->setStartValue(0.8);
    grow->setEndValue(0.9);
    grow->setEasingCurve(QEasingCurve::InOutSine);
    grow->setDuration(840);

    shrink->setTargetObject(this);
    shrink->setPropertyName("focusHaloSize");
    shrink->setStartValue(0.9);
    shrink->setEndValue(0.8);
    shrink->setEasingCurve(QEasingCurve::InOutSine);
    shrink->setDuration(840);

    group->addAnimation(grow);
    group->addAnimation(shrink);
    group->setLoopCount(-1);
    group->start();

    start();
}

FlatButtonDelegate::~FlatButtonDelegate()
{
}

void FlatButtonDelegate::setBackgroundOpacity(qreal opacity)
{
    _backgroundOpacity = opacity;
    button->update();
}

qreal FlatButtonDelegate::backgroundOpacity() const
{
    return _backgroundOpacity;
}

void FlatButtonDelegate::setBackgroundColor(const QColor &color)
{
    _backgroundColor = color;
    button->update();
}

QColor FlatButtonDelegate::backgroundColor() const
{
    return _backgroundColor;
}

void FlatButtonDelegate::setFocusHaloOpacity(qreal opacity)
{
    _focusHaloOpacity = opacity;
    button->update();
}

qreal FlatButtonDelegate::focusHaloOpacity() const
{
    return _focusHaloOpacity;
}

void FlatButtonDelegate::setFocusHaloSize(qreal size)
{
    _focusHaloSize = size;
    button->update();
}

qreal FlatButtonDelegate::focusHaloSize() const
{
    return _focusHaloSize;
}

void FlatButtonDelegate::updatePalette()
{
    QColor color;

    switch (button->role())
    {
    case Material::Primary:
        color = button->primaryTextColor();
        break;
    case Material::Secondary:
        color = button->secondaryTextColor();
        break;
    case Material::Default:
    default:
        color = button->defaultTextColor();
    }

    QPalette palette(button->palette());
    palette.setColor(QPalette::Active, QPalette::ButtonText, color);
    palette.setColor(QPalette::Inactive, QPalette::ButtonText, color);
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, button->disabledTextColor());
    button->setPalette(palette);

    _normalState->assignProperty(this, "backgroundOpacity", 0);
    _normalState->assignProperty(this, "backgroundColor", color);
    _normalState->assignProperty(this, "focusHaloOpacity", 0);

    _normalFocusedState->assignProperty(this, "backgroundOpacity", 0);
    _normalFocusedState->assignProperty(this, "backgroundColor", color);
    _normalFocusedState->assignProperty(this, "focusHaloOpacity", button->peakOpacity());

    _hoveredState->assignProperty(this, "backgroundOpacity", button->peakOpacity());
    _hoveredState->assignProperty(this, "backgroundColor", color);
    _hoveredState->assignProperty(this, "focusHaloOpacity", 0);

    _hoveredFocusedState->assignProperty(this, "backgroundOpacity", button->peakOpacity());
    _hoveredFocusedState->assignProperty(this, "backgroundColor", color);
    _normalFocusedState->assignProperty(this, "focusHaloOpacity", button->peakOpacity());

    _pressedState->assignProperty(this, "backgroundOpacity", button->peakOpacity());
    _pressedState->assignProperty(this, "backgroundColor", color);
    _pressedState->assignProperty(this, "focusHaloOpacity", 0);

    button->update();
}

void FlatButtonDelegate::addTransition(QEvent::Type eventType,
                                       QState *fromState,
                                       QState *toState)
{
    QAbstractTransition *transition = new QEventTransition(button, eventType);
    transition->setTargetState(toState);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(this, "backgroundOpacity");
    animation->setDuration(200);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this, "backgroundColor");
    animation->setDuration(200);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this, "focusHaloOpacity");
    animation->setDuration(350);
    transition->addAnimation(animation);

    fromState->addTransition(transition);
}
