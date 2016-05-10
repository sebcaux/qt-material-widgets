// @todo -- separate decl. and impl.
// inverse mode
// paint track differently left of thumb
// direct click mode (mode thumb to click pos)
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

#define THUMB_OUTER_SIZE 20

class SliderPrivate
{
    Q_DISABLE_COPY(SliderPrivate)
    Q_DECLARE_PUBLIC(Slider)

    friend class SliderThumb;

public:
    SliderPrivate(Slider *parent)
        : q_ptr(parent),
          thumb(new SliderThumb(this)),
          hoverTrack(false),
          hoverThumb(false),
          step(false),
          stepTo(0),
          oldValue(parent->value()),
          thumbSize(11),
          thumbPenWidth(0),
          thumbColor(Qt::white)
    {
        parent->setMouseTracking(true);
    }

    void init(Slider *slider)
    {
        QState *s1 = new QState(QState::ParallelStates);

        QState *s11 = new QState(s1);

        QState *inactiveState = new QState(s11);
        QState *focusState = new QState(s11);
        QState *pulseState = new QState(focusState);
        QState *pulse2State = new QState(focusState);
        QState *downState = new QState(s11);

        focusState->setInitialState(pulseState);

        inactiveState->assignProperty(thumb, "haloSize", 0);
        pulseState->assignProperty(thumb, "haloSize", 35);
        pulse2State->assignProperty(thumb, "haloSize", 28);
        downState->assignProperty(thumb, "haloSize", 0);

        inactiveState->assignProperty(slider, "thumbSize", 11);
        focusState->assignProperty(slider, "thumbSize", 11);
        downState->assignProperty(slider, "thumbSize", 17);

        machine.addState(s1);

        s11->setInitialState(inactiveState);

        //machine.addState(inactiveState);
        //machine.addState(focusState);
        //machine.addState(downState);

        //machine.setInitialState(inactiveState);

        machine.setInitialState(s1);

        QAbstractTransition *transition;
        QPropertyAnimation *animation;

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

        transition = new QSignalTransition(pulseState, SIGNAL(propertiesAssigned()));
        transition->setTargetState(pulse2State);

        animation = new QPropertyAnimation(thumb, "haloSize");
        animation->setEasingCurve(QEasingCurve::InOutSine);
        animation->setDuration(1000);
        transition->addAnimation(animation);
        pulseState->addTransition(transition);

        // Pulse out

        transition = new QSignalTransition(pulse2State, SIGNAL(propertiesAssigned()));
        transition->setTargetState(pulseState);

        animation = new QPropertyAnimation(thumb, "haloSize");
        animation->setEasingCurve(QEasingCurve::InOutSine);
        animation->setDuration(1000);
        transition->addAnimation(animation);
        pulse2State->addTransition(transition);

        // Slider pressed

        transition = new QSignalTransition(slider, SIGNAL(sliderPressed()));
        transition->setTargetState(downState);
        transition->addAnimation(new QPropertyAnimation(slider, "thumbSize"));
        transition->addAnimation(new QPropertyAnimation(thumb, "haloSize"));
        focusState->addTransition(transition);

        // Slider released

        transition = new QSignalTransition(slider, SIGNAL(sliderReleased()));
        transition->setTargetState(focusState);
        transition->addAnimation(new QPropertyAnimation(slider, "thumbSize"));
        transition->addAnimation(new QPropertyAnimation(thumb, "haloSize"));
        downState->addTransition(transition);

        //

        QState *s12 = new QState(s1);

        QState *t1 = new QState(s12);
        QState *t2 = new QState(s12);

        t1->assignProperty(slider, "thumbColor", QColor(0, 0, 0));
        t1->assignProperty(slider, "thumbPenWidth", 0);
        t2->assignProperty(slider, "thumbColor", QColor(255, 255, 255));
        t2->assignProperty(slider, "thumbPenWidth", 1.5);

        //machine.addState(t1);
        //machine.addState(t2);

        //machine.addState(s12);

        s12->setInitialState(t1);

        transition = new QSignalTransition(slider, SIGNAL(changedToMinimum()));
        transition->setTargetState(t2);
        animation = new QPropertyAnimation(slider, "thumbColor");
        animation->setDuration(700);
        transition->addAnimation(animation);
        animation = new QPropertyAnimation(slider, "thumbPenWidth");
        animation->setDuration(700);
        transition->addAnimation(animation);
        t1->addTransition(transition);

        transition = new QSignalTransition(slider, SIGNAL(changedFromMinimum()));
        transition->setTargetState(t1);
        animation = new QPropertyAnimation(slider, "thumbColor");
        animation->setDuration(700);
        transition->addAnimation(animation);
        animation = new QPropertyAnimation(slider, "thumbPenWidth");
        animation->setDuration(700);
        transition->addAnimation(animation);
        t2->addTransition(transition);

        machine.start();
    }

    QRectF trackGeometry() const
    {
        Q_Q(const Slider);

        return Qt::Horizontal == q->orientation()
            ? QRectF(THUMB_OUTER_SIZE/2, q->rect().height()/2 - 1,
                    q->rect().width() - THUMB_OUTER_SIZE, 2)
            : QRectF(q->rect().width()/2 - 1, THUMB_OUTER_SIZE/2, 2,
                    q->rect().height() - THUMB_OUTER_SIZE);
    }

    void paintTrack(QPainter *painter)
    {
        painter->save();

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor(0, 0, 0, 255));

        painter->fillRect(trackGeometry(), brush);

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

    // remove
    // remove
    // remove
    QRectF thumbGeometry() const
    {
        Q_Q(const Slider);

        return Qt::Horizontal == q->orientation()
            ? QRectF(q->thumbOffset(), q->rect().height()/2 - THUMB_OUTER_SIZE/2,
                     THUMB_OUTER_SIZE, THUMB_OUTER_SIZE)
            : QRectF(q->rect().width()/2 - THUMB_OUTER_SIZE/2, q->thumbOffset(),
                     THUMB_OUTER_SIZE, THUMB_OUTER_SIZE);
    }

    // remove
    // remove
    void paintThumb(QPainter *painter)
    {
        painter->drawRect(thumbGeometry().adjusted(0, 0, -1, -1));

        /*
        painter->save();

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(thumbColor);
        painter->setBrush(brush);

        if (thumbPenWidth) {
            QPen pen;
            pen.setWidthF(thumbPenWidth);
            painter->setPen(pen);
        } else {
            painter->setPen(Qt::NoPen);
        }

        painter->setRenderHint(QPainter::Antialiasing);

        QRectF thumb(0, 0, thumbSize, thumbSize);
        thumb.moveCenter(thumbGeometry().center());

        painter->drawEllipse(thumb);

        painter->restore();

#ifdef DEBUG_LAYOUT
        painter->drawRect(thumbGeometry());

        if (hoverThumb) {
            painter->save();
            painter->setPen(Qt::red);
            painter->drawRect(thumbGeometry());
            painter->restore();
        }
#endif
        */
    }

    int valueFromPosition(const QPoint &pos) const
    {
        Q_Q(const Slider);

        int position = Qt::Horizontal == q->orientation() ? pos.x() : pos.y();

        int span = Qt::Horizontal == q->orientation()
            ? q->rect().width() - THUMB_OUTER_SIZE
            : q->rect().height() - THUMB_OUTER_SIZE;

        return Style::sliderValueFromPosition(
                    q->minimum(),
                    q->maximum(),
                    position - THUMB_OUTER_SIZE/2,
                    span,
                    false);
    }

    Slider *const q_ptr;
    SliderThumb *const thumb;
    QStateMachine machine;
    bool   hoverTrack;
    bool   hoverThumb;
    bool   step;
    int    stepTo;
    int    oldValue;
    qreal  thumbSize;        // move VVV
    qreal  thumbPenWidth;
    QColor thumbColor;
};

#endif // SLIDER_P_H
