#include "slider_internal.h"
#include <QEvent>
#include <QPainter>
#include <QDebug>
#include <QPalette>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QEventTransition>
#include "lib/style.h"
#include "slider.h"

SliderStateMachine::SliderStateMachine(Slider *parent,
                                       SliderThumb *thumb,
                                       SliderTrack *track)
    : QStateMachine(parent),
      slider(parent),
      _track(track),
      _thumb(thumb),
      _topState(new QState(QState::ParallelStates)),
      _fstState(new QState(_topState)),
      _inactiveState(new QState(_fstState)),
      _focusState(new QState(_fstState)),
      _slidingState(new QState(_fstState)),
      _pulseOutState(new QState(_focusState)),
      _pulseInState(new QState(_focusState)),
      _sndState(new QState(_topState)),
      _minState(new QState(_sndState)),
      _normalState(new QState(_sndState))
{
    _focusState->setInitialState(_pulseOutState);

    _inactiveState->assignProperty(thumb, "haloSize", 0);
    _slidingState->assignProperty(thumb, "haloSize", 0);

    _pulseOutState->assignProperty(thumb, "haloSize", 35);
    _pulseInState->assignProperty(thumb, "haloSize", 28);

    _inactiveState->assignProperty(thumb, "diameter", 11);
    _focusState->assignProperty(thumb, "diameter", 11);
    _slidingState->assignProperty(thumb, "diameter", 17);

    addState(_topState);
    setInitialState(_topState);

    _fstState->setInitialState(_inactiveState);

    QAbstractTransition *transition;
    QPropertyAnimation *animation;

    // Show halo on mouse enter

    transition = new QSignalTransition(this, SIGNAL(noFocusMouseEnter()));
    transition->setTargetState(_focusState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    transition->addAnimation(new QPropertyAnimation(track, "fillColor", this));
    _inactiveState->addTransition(transition);

    // Show halo on focus in

    transition = new QEventTransition(parent, QEvent::FocusIn);
    transition->setTargetState(_focusState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    transition->addAnimation(new QPropertyAnimation(track, "fillColor", this));
    _inactiveState->addTransition(transition);

    // Hide halo on focus out

    transition = new QEventTransition(parent, QEvent::FocusOut);
    transition->setTargetState(_inactiveState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    transition->addAnimation(new QPropertyAnimation(track, "fillColor", this));
    _focusState->addTransition(transition);

    // Hide halo on mouse leave, except if widget has focus

    transition = new QSignalTransition(this, SIGNAL(noFocusMouseLeave()));
    transition->setTargetState(_inactiveState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    transition->addAnimation(new QPropertyAnimation(track, "fillColor", this));
    _focusState->addTransition(transition);

    // Pulse in

    transition = new QSignalTransition(_pulseOutState, SIGNAL(propertiesAssigned()));
    transition->setTargetState(_pulseInState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    animation->setDuration(1000);
    transition->addAnimation(animation);
    _pulseOutState->addTransition(transition);

    // Pulse out

    transition = new QSignalTransition(_pulseInState, SIGNAL(propertiesAssigned()));
    transition->setTargetState(_pulseOutState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    animation->setDuration(1000);
    transition->addAnimation(animation);
    _pulseInState->addTransition(transition);

    // Slider pressed

    transition = new QSignalTransition(parent, SIGNAL(sliderPressed()));
    transition->setTargetState(_slidingState);
    animation = new QPropertyAnimation(thumb, "diameter", this);
    animation->setDuration(70);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    _focusState->addTransition(transition);

    // Slider released

    transition = new QSignalTransition(parent, SIGNAL(sliderReleased()));
    transition->setTargetState(_focusState);
    animation = new QPropertyAnimation(thumb, "diameter", this);
    animation->setDuration(70);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    _slidingState->addTransition(transition);

    // Min. value transitions

    _minState->assignProperty(thumb, "borderWidth", 2);
    _normalState->assignProperty(thumb, "borderWidth", 0);

    _sndState->setInitialState(_minState);

    transition = new QSignalTransition(this, SIGNAL(changedFromMinimum()));
    transition->setTargetState(_normalState);

    animation = new QPropertyAnimation(thumb, "fillColor", this);
    animation->setDuration(200);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloColor", this);
    animation->setDuration(300);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "borderColor", this);
    animation->setDuration(200);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "borderWidth", this);
    animation->setDuration(200);
    transition->addAnimation(animation);

    _minState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(changedToMinimum()));
    transition->setTargetState(_minState);

    animation = new QPropertyAnimation(thumb, "fillColor", this);
    animation->setDuration(200);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloColor", this);
    animation->setDuration(300);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "borderColor", this);
    animation->setDuration(200);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "borderWidth", this);
    animation->setDuration(200);
    transition->addAnimation(animation);

    _normalState->addTransition(transition);

    updatePalette();
}

SliderStateMachine::~SliderStateMachine()
{
}

void SliderStateMachine::updatePalette()
{
    QColor trackColor = slider->trackColor();
    QColor thumbColor = slider->thumbColor();

    _inactiveState->assignProperty(_track, "fillColor", trackColor.lighter(130));
    _slidingState->assignProperty(_track, "fillColor", trackColor);
    _focusState->assignProperty(_track, "fillColor", trackColor);

    _minState->assignProperty(_thumb, "fillColor", slider->palette().color(QPalette::Base));
    _minState->assignProperty(_thumb, "haloColor", trackColor);
    _minState->assignProperty(_thumb, "borderColor", trackColor);

    _normalState->assignProperty(_thumb, "fillColor", thumbColor);
    _normalState->assignProperty(_thumb, "haloColor", thumbColor);
    _normalState->assignProperty(_thumb, "borderColor", thumbColor);

    slider->update();
}

SliderThumb::SliderThumb(Slider *slider)
    : QWidget(slider->parentWidget()),
      slider(slider),
      _diameter(11),
      _borderWidth(2),
      _haloSize(0)
{
    slider->installEventFilter(this);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);

    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(update()));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(update()));
}

SliderThumb::~SliderThumb()
{
}

bool SliderThumb::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::ParentChange:
        setParent(slider->parentWidget());
        break;
    case QEvent::Resize:
    case QEvent::Move:
        QWidget *widget;
        if ((widget = parentWidget())) {
            setGeometry(widget->rect());
        }
        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}

void SliderThumb::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    // Halo

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(_haloColor);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    painter.setRenderHint(QPainter::Antialiasing);

    QPointF disp = Qt::Horizontal == slider->orientation()
        ? QPointF(SLIDER_MARGIN + slider->thumbOffset(), slider->height()/2)
        : QPointF(slider->width()/2, SLIDER_MARGIN + slider->thumbOffset());

    QRectF halo((slider->pos() - QPointF(_haloSize, _haloSize)/2) + disp,
                QSizeF(_haloSize, _haloSize));

    painter.setOpacity(0.15);
    painter.drawEllipse(halo);

    // Knob

    const bool isMin = slider->value() == slider->minimum();

    brush.setColor(slider->isEnabled()
           ? _fillColor
           : slider->disabledColor());
    painter.setBrush(!slider->isEnabled() && isMin
           ? Qt::NoBrush
           : brush);

    if (slider->isEnabled() || isMin) {
        QPen pen;
        pen.setColor(_borderColor);
        pen.setWidthF((isMin && !slider->isEnabled()) ? 1.7 : _borderWidth);
        painter.setPen(pen);
    } else {
        painter.setPen(Qt::NoPen);
    }

    QRectF geometry = Qt::Horizontal == slider->orientation()
        ? QRectF(slider->thumbOffset(), slider->height()/2 - SLIDER_MARGIN,
                 SLIDER_MARGIN*2, SLIDER_MARGIN*2).translated(slider->pos())
        : QRectF(slider->width()/2 - SLIDER_MARGIN, slider->thumbOffset(),
                 SLIDER_MARGIN*2, SLIDER_MARGIN*2).translated(slider->pos());

    qreal s = slider->isEnabled() ? _diameter : 7;

    QRectF thumb(0, 0, s, s);

    thumb.moveCenter(geometry.center());

    painter.setOpacity(1);
    painter.drawEllipse(thumb);

#ifdef DEBUG_LAYOUT
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

    painter.drawRect(geometry);

    painter.drawRect(rect().adjusted(0, 0, -2, -2));
#endif
}

SliderTrack::SliderTrack(Slider *slider)
    : QWidget(slider->parentWidget()),
      slider(slider),
      _trackWidth(2)
{
    slider->installEventFilter(this);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);

    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(update()));
}

SliderTrack::~SliderTrack()
{
}

bool SliderTrack::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::ParentChange:
        setParent(slider->parentWidget());
        break;
    case QEvent::Resize:
    case QEvent::Move:
        QWidget *widget;
        if ((widget = parentWidget())) {
            setGeometry(widget->rect());
        }
        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}

void SliderTrack::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.drawRect(rect());

    QBrush fg;
    fg.setStyle(Qt::SolidPattern);
    fg.setColor(slider->isEnabled() ? slider->thumbColor()
                                    : slider->disabledColor());
    QBrush bg;
    bg.setStyle(Qt::SolidPattern);
    bg.setColor(slider->isEnabled() ? _fillColor
                                    : slider->disabledColor());

    painter.setRenderHint(QPainter::Antialiasing);

    qreal offset = slider->thumbOffset();

    if (Qt::Horizontal == slider->orientation()) {
        painter.translate(slider->x() + SLIDER_MARGIN,
                          slider->y() + slider->height()/2
                                      - static_cast<qreal>(_trackWidth)/2);
    } else {
        painter.translate(slider->x() + slider->width()/2
                                      - static_cast<qreal>(_trackWidth)/2,
                          slider->y() + SLIDER_MARGIN);
    }

    QRectF geometry = Qt::Horizontal == slider->orientation()
        ? QRectF(0, 0, slider->width() - SLIDER_MARGIN*2, _trackWidth)
        : QRectF(0, 0, _trackWidth, slider->height() - SLIDER_MARGIN*2);

    QRectF bgRect;
    QRectF fgRect;

    if (Qt::Horizontal == slider->orientation()) {
        fgRect = QRectF(0, 0, offset, _trackWidth);
        bgRect = QRectF(offset, 0, slider->width(), _trackWidth).intersected(geometry);
    } else {
        fgRect = QRectF(0, 0, _trackWidth, offset);
        bgRect = QRectF(0, offset, _trackWidth, slider->height()).intersected(geometry);
    }

    if (!slider->isEnabled()) {
        fgRect = fgRect.width() < 9 ? QRectF() : fgRect.adjusted(0, 0, -6, 0);
        bgRect = bgRect.width() < 9 ? QRectF() : bgRect.adjusted(6, 0, 0, 0);
    }

    if (slider->invertedAppearance()) {
        qSwap(bgRect, fgRect);
    }

    painter.fillRect(bgRect, bg);
    painter.fillRect(fgRect, fg);

#ifdef DEBUG_LAYOUT
    if (slider->hovered()) {
        painter.save();
        painter.setPen(Qt::red);
        painter.drawRect(geometry);
        painter.restore();
    }
#endif
}
