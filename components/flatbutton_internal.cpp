#include "flatbutton_internal.h"
#include <QAbstractTransition>
#include <QEventTransition>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QFocusEvent>
#include <QDebug>
#include "flatbutton.h"

FlatButtonDelegate::FlatButtonDelegate(FlatButton *parent)
    : QStateMachine(parent),
      button(parent),
      _normalState(new QState),
      _normalFocusedState(new QState),
      _hoveredState(new QState),
      _hoveredFocusedState(new QState),
      _pressedState(new QState),
      _haloSize(0.8),
      _haloScaleFactor(1)
{
    button->installEventFilter(this);

    addState(_normalState);
    addState(_normalFocusedState);
    addState(_hoveredState);
    addState(_hoveredFocusedState);
    addState(_pressedState);

    setInitialState(_normalState);

    addTransition(button, QEvent::FocusIn, _normalState, _normalFocusedState);
    addTransition(button, QEvent::FocusOut, _normalFocusedState, _normalState);

    addTransition(button, QEvent::Enter, _normalState, _hoveredState);
    addTransition(button, QEvent::Leave, _hoveredState, _normalState);

    addTransition(button, QEvent::Enter, _normalFocusedState, _hoveredFocusedState);
    addTransition(button, QEvent::Leave, _hoveredFocusedState, _normalFocusedState);

    addTransition(button, QEvent::FocusIn, _hoveredState, _hoveredFocusedState);
    addTransition(button, QEvent::FocusOut, _hoveredFocusedState, _hoveredState);

    addTransition(this, SIGNAL(pressed()), _hoveredState, _pressedState);
    addTransition(button, QEvent::Leave, _pressedState, _normalFocusedState);
    addTransition(button, QEvent::FocusOut, _pressedState, _hoveredState);

    _normalState->assignProperty(this, "haloSize", 0);
    _normalFocusedState->assignProperty(this, "haloSize", 0.7);
    _hoveredState->assignProperty(this, "haloSize", 0);
    _pressedState->assignProperty(this, "haloSize", 4);
    _hoveredFocusedState->assignProperty(this, "haloSize", 0.7);

    //

    QSequentialAnimationGroup *group = new QSequentialAnimationGroup(this);

    QPropertyAnimation *grow = new QPropertyAnimation(this);
    QPropertyAnimation *shrink = new QPropertyAnimation(this);

    grow->setTargetObject(this);
    grow->setPropertyName("haloScaleFactor");
    grow->setStartValue(0.8);
    grow->setEndValue(0.9);
    grow->setEasingCurve(QEasingCurve::InOutSine);
    grow->setDuration(840);

    shrink->setTargetObject(this);
    shrink->setPropertyName("haloScaleFactor");
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

void FlatButtonDelegate::setHaloOpacity(qreal opacity)
{
    _haloOpacity = opacity;
    button->update();
}

qreal FlatButtonDelegate::haloOpacity() const
{
    return _haloOpacity;
}

void FlatButtonDelegate::setHaloSize(qreal size)
{
    _haloSize = size;
    button->update();
}

qreal FlatButtonDelegate::haloSize() const
{
    return _haloSize;
}

void FlatButtonDelegate::setHaloScaleFactor(qreal size)
{
    _haloScaleFactor = size;
    button->update();
}

qreal FlatButtonDelegate::haloScaleFactor() const
{
    return _haloScaleFactor;
}

void FlatButtonDelegate::updatePalette()
{
    QColor textColor = button->textColor();
    QColor bgColor = button->backgroundColor();
    QColor disabledColor = button->disabledTextColor();

    QPalette palette(button->palette());
    palette.setColor(QPalette::Active, QPalette::ButtonText, textColor);
    palette.setColor(QPalette::Inactive, QPalette::ButtonText, textColor);
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
    button->setPalette(palette);

    qreal baseOpacity;

    if (button->isCheckable() && button->isChecked()) {
        baseOpacity = button->peakOpacity();
    } else {
        baseOpacity = 0;
    }

    _normalState->assignProperty(this, "backgroundOpacity", baseOpacity);
    _normalState->assignProperty(this, "backgroundColor", bgColor);
    _normalState->assignProperty(this, "haloOpacity", 0);

    _normalFocusedState->assignProperty(this, "backgroundOpacity", baseOpacity);
    _normalFocusedState->assignProperty(this, "backgroundColor", bgColor);
    _normalFocusedState->assignProperty(this, "haloOpacity", button->peakOpacity());

    _hoveredState->assignProperty(this, "backgroundOpacity", button->peakOpacity());
    _hoveredState->assignProperty(this, "backgroundColor", bgColor);
    _hoveredState->assignProperty(this, "haloOpacity", 0);

    _hoveredFocusedState->assignProperty(this, "backgroundOpacity", button->peakOpacity());
    _hoveredFocusedState->assignProperty(this, "backgroundColor", bgColor);
    _hoveredFocusedState->assignProperty(this, "haloOpacity", button->peakOpacity());

    button->update();
}

bool FlatButtonDelegate::eventFilter(QObject *watched, QEvent *event)
{
    if (QEvent::FocusIn == event->type()) {
        QFocusEvent *focusEvent = static_cast<QFocusEvent *>(event);
        if (focusEvent && Qt::MouseFocusReason == focusEvent->reason()) {
            emit pressed();
            return true;
        }
    }
    if (button->isCheckable()) {
        updatePalette();
    }
    return QStateMachine::eventFilter(watched, event);
}

void FlatButtonDelegate::addTransition(QObject *object,
                                       const char *signal,
                                       QState *fromState,
                                       QState *toState)
{
    addTransition(new QSignalTransition(object, signal), fromState, toState);
}

void FlatButtonDelegate::addTransition(QObject *object,
                                       QEvent::Type eventType,
                                       QState *fromState,
                                       QState *toState)
{
    addTransition(new QEventTransition(object, eventType), fromState, toState);
}

void FlatButtonDelegate::addTransition(QAbstractTransition *transition,
                                       QState *fromState,
                                       QState *toState)
{
    transition->setTargetState(toState);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(this, "backgroundOpacity", this);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this, "backgroundColor", this);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this, "haloOpacity", this);
    animation->setDuration(170);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this, "haloSize", this);
    animation->setDuration(350);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    transition->addAnimation(animation);

    fromState->addTransition(transition);
}
