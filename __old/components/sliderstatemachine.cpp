#include "sliderstatemachine.h"
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QEventTransition>
#include "lib/style.h"
#include "slider.h"
#include "sliderthumb.h"
#include "slidertrack.h"

SliderStateMachine::SliderStateMachine(Slider *parent,
                                       SliderThumb *thumb,
                                       SliderTrack *track)
    : QStateMachine(parent)
{
    Style &style = Style::instance();

    QState *topState = new QState(QState::ParallelStates);

    QState *fstState = new QState(topState);

    QState *inactiveState = new QState(fstState);
    QState *focusState = new QState(fstState);
    QState *slidingState = new QState(fstState);
    QState *disabledState = new QState(fstState);

    QState *pulseOutState = new QState(focusState);
    QState *pulseInState = new QState(focusState);

    focusState->setInitialState(pulseOutState);

    inactiveState->assignProperty(thumb, "haloSize", 0);
    slidingState->assignProperty(thumb, "haloSize", 0);

    pulseOutState->assignProperty(thumb, "haloSize", 35);
    pulseInState->assignProperty(thumb, "haloSize", 28);

    disabledState->assignProperty(thumb, "diameter", 7);
    disabledState->assignProperty(thumb, "fillColor", style.themeColor("disabled"));

    inactiveState->assignProperty(thumb, "diameter", 11);
    focusState->assignProperty(thumb, "diameter", 11);
    slidingState->assignProperty(thumb, "diameter", 17);

    QColor fillColor = style.themeColor("primary1");

    inactiveState->assignProperty(thumb, "fillColor", fillColor);
    focusState->assignProperty(thumb, "fillColor", fillColor);
    slidingState->assignProperty(thumb, "fillColor", fillColor);

    inactiveState->assignProperty(track, "fillColor", style.themeColor("accent2"));
    slidingState->assignProperty(track, "fillColor", style.themeColor("accent3"));
    focusState->assignProperty(track, "fillColor", style.themeColor("accent3"));
    disabledState->assignProperty(track, "fillColor", style.themeColor("disabled"));

    addState(topState);

    fstState->setInitialState(inactiveState);

    setInitialState(topState);

    QAbstractTransition *transition;
    QPropertyAnimation *animation;

    // Add transitions

    transition = new QSignalTransition(this, SIGNAL(sliderDisabled()));
    transition->setTargetState(disabledState);
    inactiveState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(sliderDisabled()));
    transition->setTargetState(disabledState);
    focusState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(sliderDisabled()));
    transition->setTargetState(disabledState);
    slidingState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(sliderEnabled()));
    transition->setTargetState(inactiveState);
    disabledState->addTransition(transition);

    // Show halo on mouse enter

    transition = new QSignalTransition(this, SIGNAL(noFocusMouseEnter()));
    transition->setTargetState(focusState);

    animation = new QPropertyAnimation(thumb, "haloSize");
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    transition->addAnimation(new QPropertyAnimation(track, "fillColor"));
    inactiveState->addTransition(transition);

    // Show halo on focus in

    transition = new QEventTransition(parent, QEvent::FocusIn);
    transition->setTargetState(focusState);

    animation = new QPropertyAnimation(thumb, "haloSize");
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    transition->addAnimation(new QPropertyAnimation(track, "fillColor"));
    inactiveState->addTransition(transition);

    // Hide halo on focus out

    transition = new QEventTransition(parent, QEvent::FocusOut);
    transition->setTargetState(inactiveState);

    animation = new QPropertyAnimation(thumb, "haloSize");
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    transition->addAnimation(new QPropertyAnimation(track, "fillColor"));
    focusState->addTransition(transition);

    // Hide halo on mouse leave, except if widget has focus

    transition = new QSignalTransition(this, SIGNAL(noFocusMouseLeave()));
    transition->setTargetState(inactiveState);

    animation = new QPropertyAnimation(thumb, "haloSize");
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    transition->addAnimation(new QPropertyAnimation(track, "fillColor"));
    focusState->addTransition(transition);

    // Pulse in

    transition = new QSignalTransition(pulseOutState, SIGNAL(propertiesAssigned()));
    transition->setTargetState(pulseInState);

    animation = new QPropertyAnimation(thumb, "haloSize");
    animation->setEasingCurve(QEasingCurve::InOutSine);
    animation->setDuration(1000);
    transition->addAnimation(animation);
    pulseOutState->addTransition(transition);

    // Pulse out

    transition = new QSignalTransition(pulseInState, SIGNAL(propertiesAssigned()));
    transition->setTargetState(pulseOutState);

    animation = new QPropertyAnimation(thumb, "haloSize");
    animation->setEasingCurve(QEasingCurve::InOutSine);
    animation->setDuration(1000);
    transition->addAnimation(animation);
    pulseInState->addTransition(transition);

    // Slider pressed

    transition = new QSignalTransition(parent, SIGNAL(sliderPressed()));
    transition->setTargetState(slidingState);
    animation = new QPropertyAnimation(thumb, "diameter");
    animation->setDuration(70);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloSize");
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    focusState->addTransition(transition);

    // Slider released

    transition = new QSignalTransition(parent, SIGNAL(sliderReleased()));
    transition->setTargetState(focusState);
    animation = new QPropertyAnimation(thumb, "diameter");
    animation->setDuration(70);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloSize");
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    slidingState->addTransition(transition);

    // Min. value transitions

    QState *sndState = new QState(topState);

    QState *minState = new QState(sndState);
    QState *normalState = new QState(sndState);

    QColor minHaloColor = style.themeColor("accent3");
    minHaloColor.setAlphaF(0.15);

    QColor haloColor = style.themeColor("primary1");
    haloColor.setAlphaF(0.15);

    QColor canvasColor = style.themeColor("canvas");

    minState->assignProperty(thumb, "minFillColor", canvasColor);
    minState->assignProperty(thumb, "fillColor", canvasColor);
    minState->assignProperty(thumb, "haloColor", minHaloColor);
    minState->assignProperty(thumb, "borderWidth", 2);
    normalState->assignProperty(thumb, "fillColor", fillColor);
    normalState->assignProperty(thumb, "minFillColor", fillColor);
    normalState->assignProperty(thumb, "haloColor", haloColor);
    normalState->assignProperty(thumb, "borderWidth", 0);

    sndState->setInitialState(minState);

    transition = new QSignalTransition(this, SIGNAL(changedFromMinimum()));
    transition->setTargetState(normalState);

    animation = new QPropertyAnimation(thumb, "fillColor");
    animation->setDuration(200);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloColor");
    animation->setDuration(200);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "borderWidth");
    animation->setDuration(400);
    transition->addAnimation(animation);

    minState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(changedToMinimum()));
    transition->setTargetState(minState);

    animation = new QPropertyAnimation(thumb, "minFillColor");
    animation->setDuration(200);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloColor");
    animation->setDuration(200);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "borderWidth");
    animation->setDuration(400);
    transition->addAnimation(animation);

    normalState->addTransition(transition);
}

SliderStateMachine::~SliderStateMachine()
{
}
