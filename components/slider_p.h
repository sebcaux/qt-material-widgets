#ifndef SLIDER_P_H
#define SLIDER_P_H

#include "slider.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QStateMachine>
#include <QEventTransition>
#include <QSignalTransition>
#include <QDebug>
#include "lib/style.h"
#include "sliderthumb.h"

class SliderPrivate
{
    Q_DISABLE_COPY(SliderPrivate)
    Q_DECLARE_PUBLIC(Slider)

    friend class SliderThumb;

public:
    SliderPrivate(Slider *parent);

    void init(Slider *slider);

    QRectF trackGeometry() const;
    QRectF thumbGeometry() const;

    void paintTrack(QPainter *painter);
    int valueFromPosition(const QPoint &pos) const;

    Slider *const q_ptr;
    SliderThumb *const thumb;
    QStateMachine machine;
    bool hoverTrack;
    bool hoverThumb;
    bool step;
    bool pageStepMode;
    int  stepTo;
    int  oldValue;
    QColor trackColor;
};

SliderPrivate::SliderPrivate(Slider *parent)
    : q_ptr(parent),
      thumb(new SliderThumb(parent)),
      hoverTrack(false),
      hoverThumb(false),
      step(false),
      pageStepMode(false),
      stepTo(0),
      oldValue(parent->value()),
      trackColor(QColor(200, 200, 200))
{
    parent->setMouseTracking(true);
}

void SliderPrivate::init(Slider *slider)
{
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
    disabledState->assignProperty(thumb, "fillColor", QColor(200, 200, 200));

    inactiveState->assignProperty(thumb, "diameter", 11);
    focusState->assignProperty(thumb, "diameter", 11);
    slidingState->assignProperty(thumb, "diameter", 17);

    inactiveState->assignProperty(thumb, "fillColor", QColor(0, 0, 0));
    focusState->assignProperty(thumb, "fillColor", QColor(0, 0, 0));
    slidingState->assignProperty(thumb, "fillColor", QColor(0, 0, 0));

    machine.addState(topState);

    fstState->setInitialState(inactiveState);

    machine.setInitialState(topState);

    QAbstractTransition *transition;
    QPropertyAnimation *animation;

    //

    transition = new QSignalTransition(slider, SIGNAL(sliderDisabled()));
    transition->setTargetState(disabledState);
    inactiveState->addTransition(transition);

    transition = new QSignalTransition(slider, SIGNAL(sliderDisabled()));
    transition->setTargetState(disabledState);
    focusState->addTransition(transition);

    transition = new QSignalTransition(slider, SIGNAL(sliderDisabled()));
    transition->setTargetState(disabledState);
    slidingState->addTransition(transition);

    transition = new QSignalTransition(slider, SIGNAL(sliderEnabled()));
    transition->setTargetState(inactiveState);
    disabledState->addTransition(transition);

    // Show halo on focus in

    transition = new QEventTransition(slider, QEvent::FocusIn);
    transition->setTargetState(focusState);

    animation = new QPropertyAnimation(thumb, "haloSize");
    transition->addAnimation(animation);
    inactiveState->addTransition(transition);

    // Hide halo on focus out

    transition = new QEventTransition(slider, QEvent::FocusOut);
    transition->setTargetState(inactiveState);

    animation = new QPropertyAnimation(thumb, "haloSize");
    transition->addAnimation(animation);
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

    transition = new QSignalTransition(slider, SIGNAL(sliderPressed()));
    transition->setTargetState(slidingState);
    transition->addAnimation(new QPropertyAnimation(thumb, "diameter"));
    transition->addAnimation(new QPropertyAnimation(thumb, "haloSize"));
    focusState->addTransition(transition);

    // Slider released

    transition = new QSignalTransition(slider, SIGNAL(sliderReleased()));
    transition->setTargetState(focusState);
    transition->addAnimation(new QPropertyAnimation(thumb, "diameter"));
    transition->addAnimation(new QPropertyAnimation(thumb, "haloSize"));
    slidingState->addTransition(transition);

    // Min. value animation

    QState *sndState = new QState(topState);

    QState *minState = new QState(sndState);
    QState *normalState = new QState(sndState);

    minState->assignProperty(thumb, "minFillColor", QColor(255, 255, 255));
    minState->assignProperty(thumb, "fillColor", QColor(255, 255, 255));
    minState->assignProperty(thumb, "borderWidth", 2);
    normalState->assignProperty(thumb, "fillColor", QColor(0, 0, 0));
    normalState->assignProperty(thumb, "minFillColor", QColor(0, 0, 0));
    normalState->assignProperty(thumb, "borderWidth", 0);

    sndState->setInitialState(minState);

    transition = new QSignalTransition(slider, SIGNAL(changedFromMinimum()));
    transition->setTargetState(normalState);
    animation = new QPropertyAnimation(thumb, "fillColor");
    animation->setDuration(200);
    transition->addAnimation(animation);
    minState->addTransition(transition);

    transition = new QSignalTransition(slider, SIGNAL(changedToMinimum()));
    transition->setTargetState(minState);
    animation = new QPropertyAnimation(thumb, "minFillColor");
    animation->setDuration(200);
    transition->addAnimation(animation);
    normalState->addTransition(transition);

    machine.start();
}

QRectF SliderPrivate::trackGeometry() const
{
    Q_Q(const Slider);

    return Qt::Horizontal == q->orientation()
        ? QRectF(SLIDER_MARGIN, q->rect().height()/2 - 1,
                q->rect().width() - SLIDER_MARGIN*2, 2)
        : QRectF(q->rect().width()/2 - 1, SLIDER_MARGIN, 2,
                q->rect().height() - SLIDER_MARGIN*2);
}

QRectF SliderPrivate::thumbGeometry() const
{
    Q_Q(const Slider);

    return Qt::Horizontal == q->orientation()
        ? QRectF(q->thumbOffset(), q->rect().height()/2 - SLIDER_MARGIN,
                 SLIDER_MARGIN*2, SLIDER_MARGIN*2)
        : QRectF(q->rect().width()/2 - SLIDER_MARGIN, q->thumbOffset(),
                 SLIDER_MARGIN*2, SLIDER_MARGIN*2);
}

void SliderPrivate::paintTrack(QPainter *painter)
{
    Q_Q(const Slider);

    painter->save();

    QBrush fg;
    fg.setStyle(Qt::SolidPattern);
    fg.setColor(thumb->fillColor());

    QBrush bg;
    bg.setStyle(Qt::SolidPattern);
    bg.setColor(trackColor);

    qreal offset = q->thumbOffset() + SLIDER_MARGIN;

    QSizeF box(q->isEnabled() ? offset : offset - 7,
               qMax(q->width(), q->height()));

    if (Qt::Vertical == q->orientation())
        box.transpose();

    QRectF rect = Qt::Vertical == q->orientation()
        ? QRectF(0, q->isEnabled() ? offset : offset + 7,
                 box.width(), box.width())
        : QRectF(q->isEnabled() ? offset : offset + 7, 0,
                 box.height(), box.height());

    bool inverted = q->invertedAppearance();

    painter->fillRect(QRectF(QPointF(0, 0), box).intersected(trackGeometry()),
                      inverted ? bg : fg);
    painter->fillRect(rect.intersected(trackGeometry()), inverted ? fg : bg);

    painter->restore();

#ifdef DEBUG_LAYOUT
    if (hoverTrack) {
        painter->save();
        painter->setPen(Qt::red);
        painter->drawRect(trackGeometry());
        painter->restore();
    }
#endif
}

int SliderPrivate::valueFromPosition(const QPoint &pos) const
{
    Q_Q(const Slider);

    int position = Qt::Horizontal == q->orientation() ? pos.x() : pos.y();

    int span = Qt::Horizontal == q->orientation()
        ? q->rect().width() - SLIDER_MARGIN*2
        : q->rect().height() - SLIDER_MARGIN*2;

    return Style::sliderValueFromPosition(
                q->minimum(),
                q->maximum(),
                position - SLIDER_MARGIN,
                span,
                q->invertedAppearance());
}

#endif // SLIDER_P_H
