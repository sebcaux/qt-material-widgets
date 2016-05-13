#include "sliderinternal.h"
#include <QEvent>
#include <QPainter>
#include <QDebug>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QEventTransition>
#include "lib/style.h"
#include "slider.h"

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
    QEvent::Type type = event->type();

    if (QEvent::ParentChange == type) {
        setParent(slider->parentWidget());
    } else if (QEvent::Resize == type || QEvent::Move == type) {
        QWidget *widget;
        if ((widget = parentWidget())) {
            setGeometry(widget->rect());
        }
    }
    return QWidget::eventFilter(obj, event);
}

void SliderThumb::paintEvent(QPaintEvent *event)
{
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

    painter.drawEllipse(halo);

    // Knob

    brush.setColor(slider->value() > slider->minimum()
       ? (slider->isEnabled()
          ? _fillColor : Style::instance().themeColor("disabled"))
       : _minFillColor);
    painter.setBrush(brush);

    if (_borderWidth > 0) {
        QPen pen;
        pen.setColor(Style::instance().themeColor("accent3"));
        pen.setWidthF(_borderWidth);
        painter.setPen(pen);
    } else {
        painter.setPen(Qt::NoPen);
    }

    QRectF geometry = Qt::Horizontal == slider->orientation()
        ? QRectF(slider->thumbOffset(), slider->height()/2 - SLIDER_MARGIN,
                 SLIDER_MARGIN*2, SLIDER_MARGIN*2).translated(slider->pos())
        : QRectF(slider->width()/2 - SLIDER_MARGIN, slider->thumbOffset(),
                 SLIDER_MARGIN*2, SLIDER_MARGIN*2).translated(slider->pos());

    QRectF thumb(0, 0, _diameter, _diameter);

    thumb.moveCenter(geometry.center());

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

    QWidget::paintEvent(event);
}

SliderTrack::SliderTrack(Slider *slider)
    : QWidget(slider->parentWidget()),
      slider(slider),
      _width(2)
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
    QEvent::Type type = event->type();

    if (QEvent::ParentChange == type) {
        setParent(slider->parentWidget());
    } else if (QEvent::Resize == type || QEvent::Move == type) {
        if (parentWidget()) {
            setGeometry(parentWidget()->rect());
        }
    }
    return QWidget::eventFilter(obj, event);
}

void SliderTrack::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    Style &style = Style::instance();

    QBrush fg;
    fg.setStyle(Qt::SolidPattern);
    fg.setColor(slider->isEnabled() ? style.themeColor("primary1")
                                    : style.themeColor("disabled"));
    QBrush bg;
    bg.setStyle(Qt::SolidPattern);
    bg.setColor(slider->isEnabled() ? _fillColor
                                    : style.themeColor("disabled"));

    painter.setRenderHint(QPainter::Antialiasing);

    qreal offset = slider->thumbOffset();

    if (Qt::Horizontal == slider->orientation()) {
        painter.translate(slider->x() + SLIDER_MARGIN,
                          slider->y() + slider->height()/2
                                      - static_cast<qreal>(_width)/2);
    } else {
        painter.translate(slider->x() + slider->width()/2
                                      - static_cast<qreal>(_width)/2,
                          slider->y() + SLIDER_MARGIN);
    }

    QRectF geometry = Qt::Horizontal == slider->orientation()
        ? QRectF(0, 0, slider->width() - SLIDER_MARGIN*2, _width)
        : QRectF(0, 0, _width, slider->height() - SLIDER_MARGIN*2);

    QRectF bgRect;
    QRectF fgRect;

    if (Qt::Horizontal == slider->orientation()) {
        fgRect = QRectF(0, 0, offset, _width);
        bgRect = QRectF(offset, 0, slider->width(), _width).intersected(geometry);
    } else {
        fgRect = QRectF(0, 0, _width, offset);
        bgRect = QRectF(0, offset, _width, slider->height()).intersected(geometry);
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

    QWidget::paintEvent(event);
}
