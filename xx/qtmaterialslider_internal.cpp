#include "xx/qtmaterialslider_internal.h"
#include <QState>
#include <QAbstractTransition>
#include <QSignalTransition>
#include <QEventTransition>
#include <QPropertyAnimation>
#include <QPainter>
#include "xx/qtmaterialslider.h"
#include "xxlib/qtmaterialstyle.h"

enum {
    SliderMargin = 30
};

/*!
 *  \class QtMaterialSliderStateMachine
 *  \internal
 */

QtMaterialSliderStateMachine::QtMaterialSliderStateMachine(
        QtMaterialSlider      *slider,
        QtMaterialSliderThumb *thumb,
        QtMaterialSliderTrack *track)
    : QStateMachine(slider),
      m_slider(slider),
      m_thumb(thumb),
      m_track(track),
      m_topState(new QState(QState::ParallelStates)),
      m_fstState(new QState(m_topState)),
      m_sndState(new QState(m_topState)),
      m_inactiveState(new QState(m_fstState)),
      m_focusState(new QState(m_fstState)),
      m_slidingState(new QState(m_fstState)),
      m_pulseOutState(new QState(m_focusState)),
      m_pulseInState(new QState(m_focusState)),
      m_minState(new QState(m_sndState)),
      m_normalState(new QState(m_sndState))
{
    addState(m_topState);
    setInitialState(m_topState);

    m_fstState->setInitialState(m_inactiveState);
    m_focusState->setInitialState(m_pulseOutState);

    m_inactiveState->assignProperty(thumb, "haloSize", 0);
    m_slidingState->assignProperty(thumb, "haloSize", 0);

    m_pulseOutState->assignProperty(thumb, "haloSize", 35);
    m_pulseInState->assignProperty(thumb, "haloSize", 28);

    m_inactiveState->assignProperty(thumb, "diameter", 11);
    m_focusState->assignProperty(thumb, "diameter", 11);
    m_slidingState->assignProperty(thumb, "diameter", 17);

    QAbstractTransition *transition;
    QPropertyAnimation *animation;

    // Show halo on mouse enter

    transition = new QSignalTransition(this, SIGNAL(noFocusMouseEnter()));
    transition->setTargetState(m_focusState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    transition->addAnimation(new QPropertyAnimation(track, "fillColor", this));
    m_inactiveState->addTransition(transition);

    // Show halo on focus in

    transition = new QEventTransition(slider, QEvent::FocusIn);
    transition->setTargetState(m_focusState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    transition->addAnimation(new QPropertyAnimation(track, "fillColor", this));
    m_inactiveState->addTransition(transition);

    // Hide halo on focus out

    transition = new QEventTransition(slider, QEvent::FocusOut);
    transition->setTargetState(m_inactiveState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    transition->addAnimation(new QPropertyAnimation(track, "fillColor", this));
    m_focusState->addTransition(transition);

    // Hide halo on mouse leave, except if widget has focus

    transition = new QSignalTransition(this, SIGNAL(noFocusMouseLeave()));
    transition->setTargetState(m_inactiveState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    transition->addAnimation(new QPropertyAnimation(track, "fillColor", this));
    m_focusState->addTransition(transition);

    // Pulse in

    transition = new QSignalTransition(m_pulseOutState, SIGNAL(propertiesAssigned()));
    transition->setTargetState(m_pulseInState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    animation->setDuration(1000);
    transition->addAnimation(animation);
    m_pulseOutState->addTransition(transition);

    // Pulse out

    transition = new QSignalTransition(m_pulseInState, SIGNAL(propertiesAssigned()));
    transition->setTargetState(m_pulseOutState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    animation->setDuration(1000);
    transition->addAnimation(animation);
    m_pulseInState->addTransition(transition);

    // Slider pressed

    transition = new QSignalTransition(slider, SIGNAL(sliderPressed()));
    transition->setTargetState(m_slidingState);
    animation = new QPropertyAnimation(thumb, "diameter", this);
    animation->setDuration(70);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    m_focusState->addTransition(transition);

    // Slider released

    transition = new QSignalTransition(slider, SIGNAL(sliderReleased()));
    transition->setTargetState(m_focusState);
    animation = new QPropertyAnimation(thumb, "diameter", this);
    animation->setDuration(70);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    m_slidingState->addTransition(transition);

    // Min. value transitions

    m_minState->assignProperty(thumb, "borderWidth", 2);
    m_normalState->assignProperty(thumb, "borderWidth", 0);

    m_sndState->setInitialState(m_minState);

    transition = new QSignalTransition(this, SIGNAL(changedFromMinimum()));
    transition->setTargetState(m_normalState);

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

    m_minState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(changedToMinimum()));
    transition->setTargetState(m_minState);

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

    m_normalState->addTransition(transition);

    setupProperties();
}

QtMaterialSliderStateMachine::~QtMaterialSliderStateMachine()
{
}

void QtMaterialSliderStateMachine::setupProperties()
{
    QColor trackColor = m_slider->trackColor();
    QColor thumbColor = m_slider->thumbColor();

    m_inactiveState->assignProperty(m_track, "fillColor", trackColor.lighter(130));
    m_slidingState->assignProperty(m_track, "fillColor", trackColor);
    m_focusState->assignProperty(m_track, "fillColor", trackColor);

    //m_minState->assignProperty(_thumb, "fillColor", slider->palette().color(QPalette::Base));
    m_minState->assignProperty(m_thumb, "fillColor", QColor(Qt::red));
    m_minState->assignProperty(m_thumb, "haloColor", trackColor);
    m_minState->assignProperty(m_thumb, "borderColor", trackColor);

    m_normalState->assignProperty(m_thumb, "fillColor", thumbColor);
    m_normalState->assignProperty(m_thumb, "haloColor", thumbColor);
    m_normalState->assignProperty(m_thumb, "borderColor", thumbColor);

    m_slider->update();
}

/*!
 *  \class QtMaterialSliderThumb
 *  \internal
 */

QtMaterialSliderThumb::QtMaterialSliderThumb(QtMaterialSlider *slider)
    : QtMaterialOverlayWidget(slider->parentWidget()),
      m_slider(slider),
      m_diameter(11),
      m_borderWidth(2),
      m_haloSize(0)
{
    slider->installEventFilter(this);

    setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

QtMaterialSliderThumb::~QtMaterialSliderThumb()
{
}

bool QtMaterialSliderThumb::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::ParentChange == event->type()) {
        setParent(m_slider->parentWidget());
    }

    return QtMaterialOverlayWidget::eventFilter(obj, event);
}

void QtMaterialSliderThumb::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Halo

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(m_haloColor);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    QPointF disp = Qt::Horizontal == m_slider->orientation()
        ? QPointF(SliderMargin + m_slider->thumbOffset(), m_slider->height()/2)
        : QPointF(m_slider->width()/2, SliderMargin + m_slider->thumbOffset());

    QRectF halo((m_slider->pos() - QPointF(m_haloSize, m_haloSize)/2) + disp,
                QSizeF(m_haloSize, m_haloSize));

    painter.setOpacity(0.15);
    painter.drawEllipse(halo);

    // Knob

    const bool isMin = m_slider->value() == m_slider->minimum();

    brush.setColor(m_slider->isEnabled()
           ? m_fillColor
           : m_slider->disabledColor());
    painter.setBrush(!m_slider->isEnabled() && isMin
           ? Qt::NoBrush
           : brush);

    if (m_slider->isEnabled() || isMin) {
        QPen pen;
        pen.setColor(m_borderColor);
        pen.setWidthF((isMin && !m_slider->isEnabled()) ? 1.7 : m_borderWidth);
        painter.setPen(pen);
    } else {
        painter.setPen(Qt::NoPen);
    }

    QRectF geometry = Qt::Horizontal == m_slider->orientation()
        ? QRectF(m_slider->thumbOffset(), m_slider->height()/2 - SliderMargin,
                 SliderMargin*2, SliderMargin*2).translated(m_slider->pos())
        : QRectF(m_slider->width()/2 - SliderMargin, m_slider->thumbOffset(),
                 SliderMargin*2, SliderMargin*2).translated(m_slider->pos());

    qreal s = m_slider->isEnabled() ? m_diameter : 7;

    QRectF thumb(0, 0, s, s);

    thumb.moveCenter(geometry.center());

    painter.setOpacity(1);
    painter.drawEllipse(thumb);
}

/*!
 *  \class QtMaterialSliderTrack
 *  \internal
 */

QtMaterialSliderTrack::QtMaterialSliderTrack(QtMaterialSlider *slider)
    : QtMaterialOverlayWidget(slider->parentWidget()),
      m_slider(slider),
      m_trackWidth(2)
{
    slider->installEventFilter(this);

    setAttribute(Qt::WA_TransparentForMouseEvents, true);

    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(update()));
}

QtMaterialSliderTrack::~QtMaterialSliderTrack()
{
}

bool QtMaterialSliderTrack::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::ParentChange == event->type()) {
        setParent(m_slider->parentWidget());
    }

    return QtMaterialOverlayWidget::eventFilter(obj, event);
}

void QtMaterialSliderTrack::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush fg;
    fg.setStyle(Qt::SolidPattern);
    fg.setColor(m_slider->isEnabled() ? m_slider->thumbColor()
                                      : m_slider->disabledColor());
    QBrush bg;
    bg.setStyle(Qt::SolidPattern);
    bg.setColor(m_slider->isEnabled() ? m_fillColor
                                      : m_slider->disabledColor());

    qreal offset = m_slider->thumbOffset();

    if (Qt::Horizontal == m_slider->orientation()) {
        painter.translate(m_slider->x() + SliderMargin,
                          m_slider->y() + m_slider->height()/2
                                        - static_cast<qreal>(m_trackWidth)/2);
    } else {
        painter.translate(m_slider->x() + m_slider->width()/2
                                        - static_cast<qreal>(m_trackWidth)/2,
                          m_slider->y() + SliderMargin);
    }

    QRectF geometry = Qt::Horizontal == m_slider->orientation()
        ? QRectF(0, 0, m_slider->width() - SliderMargin*2, m_trackWidth)
        : QRectF(0, 0, m_trackWidth, m_slider->height() - SliderMargin*2);

    QRectF bgRect;
    QRectF fgRect;

    if (Qt::Horizontal == m_slider->orientation()) {
        fgRect = QRectF(0, 0, offset, m_trackWidth);
        bgRect = QRectF(offset, 0, m_slider->width(), m_trackWidth).intersected(geometry);
    } else {
        fgRect = QRectF(0, 0, m_trackWidth, offset);
        bgRect = QRectF(0, offset, m_trackWidth, m_slider->height()).intersected(geometry);
    }

    if (!m_slider->isEnabled()) {
        fgRect = fgRect.width() < 9 ? QRectF() : fgRect.adjusted(0, 0, -6, 0);
        bgRect = bgRect.width() < 9 ? QRectF() : bgRect.adjusted(6, 0, 0, 0);
    }

    if (m_slider->invertedAppearance()) {
        qSwap(bgRect, fgRect);
    }

    painter.fillRect(bgRect, bg);
    painter.fillRect(fgRect, fg);
}
