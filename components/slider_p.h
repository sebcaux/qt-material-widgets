#ifndef SLIDER_P_H
#define SLIDER_P_H

#include <QPainter>
#include <QPropertyAnimation>
#include <QStateMachine>
#include <QEventTransition>
#include <QSignalTransition>
#include <QDebug>
#include "slider.h"
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

    void setHovered(bool hovered);

    Slider *const q_ptr;
    SliderThumb *const thumb;
    QStateMachine machine;
    bool hoverTrack;
    bool hoverThumb;
    bool hover;
    bool step;
    bool pageStepMode;
    int  stepTo;
    int  oldValue;
    int  trackWidth;
};

SliderPrivate::SliderPrivate(Slider *parent)
    : q_ptr(parent),
      thumb(new SliderThumb(parent)),
      hoverTrack(false),
      hoverThumb(false),
      hover(false),
      step(false),
      pageStepMode(false),
      stepTo(0),
      oldValue(parent->value()),
      trackWidth(2)
{
    parent->setMouseTracking(true);
}

void SliderPrivate::init(Slider *slider)
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

    machine.addState(topState);

    fstState->setInitialState(inactiveState);

    machine.setInitialState(topState);

    QAbstractTransition *transition;
    QPropertyAnimation *animation;

    // Add transitions

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

    // Show halo on mouse enter

    transition = new QSignalTransition(slider, SIGNAL(mouseEnter()));
    transition->setTargetState(focusState);

    animation = new QPropertyAnimation(thumb, "haloSize");
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    inactiveState->addTransition(transition);

    // Show halo on focus in

    transition = new QEventTransition(slider, QEvent::FocusIn);
    transition->setTargetState(focusState);

    animation = new QPropertyAnimation(thumb, "haloSize");
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    inactiveState->addTransition(transition);

    // Hide halo on focus out

    transition = new QEventTransition(slider, QEvent::FocusOut);
    transition->setTargetState(inactiveState);

    animation = new QPropertyAnimation(thumb, "haloSize");
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    focusState->addTransition(transition);

    // Hide halo on mouse leave, except if widget has focus

    transition = new QSignalTransition(slider, SIGNAL(mouseLeave()));
    transition->setTargetState(inactiveState);

    animation = new QPropertyAnimation(thumb, "haloSize");
    animation->setEasingCurve(QEasingCurve::InOutSine);
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

    animation = new QPropertyAnimation(thumb, "haloSize");
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    focusState->addTransition(transition);

    // Slider released

    transition = new QSignalTransition(slider, SIGNAL(sliderReleased()));
    transition->setTargetState(focusState);
    transition->addAnimation(new QPropertyAnimation(thumb, "diameter"));

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

    transition = new QSignalTransition(slider, SIGNAL(changedFromMinimum()));
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

    transition = new QSignalTransition(slider, SIGNAL(changedToMinimum()));
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

    machine.start();

    // End of state machine code

    slider->setFocusPolicy(Qt::StrongFocus);

    QSizePolicy sp(QSizePolicy::Expanding, QSizePolicy::Fixed);
    if (slider->orientation() == Qt::Vertical)
        sp.transpose();
    slider->setSizePolicy(sp);
    slider->setAttribute(Qt::WA_WState_OwnSizePolicy, false);

    QCoreApplication::processEvents();
}

QRectF SliderPrivate::trackGeometry() const
{
    Q_Q(const Slider);

    qreal hw = static_cast<qreal>(trackWidth)/2;

    return Qt::Horizontal == q->orientation()
        ? QRectF(SLIDER_MARGIN, q->rect().height()/2 - hw,
                q->rect().width() - SLIDER_MARGIN*2, hw*2)
        : QRectF(q->rect().width()/2 - hw, SLIDER_MARGIN, hw*2,
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

    Style &style = Style::instance();

    painter->save();

    QBrush fg;
    fg.setStyle(Qt::SolidPattern);
    fg.setColor(q->isEnabled() ? style.themeColor("primary1")
                               : style.themeColor("disabled"));
    QBrush bg;
    bg.setStyle(Qt::SolidPattern);
    bg.setColor(hover ? QColor(0, 0, 0, 150)          // @TODO: set theme color
                      : style.themeColor("accent3"));

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

void SliderPrivate::setHovered(bool hovered)
{
    Q_Q(Slider);

    if (hover != hovered) {
        hover = hovered;
        if (!q->hasFocus())  {
            if (hovered) {
                emit q->mouseEnter();
            } else {
                emit q->mouseLeave();
            }
        }
        q->update();
    }
}

#endif // SLIDER_P_H
