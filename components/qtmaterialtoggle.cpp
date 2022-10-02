#include "qtmaterialtoggle.h"

#include "lib/qtmaterialstyle.h"
#include "qtmaterialtoggle_internal.h"
#include "qtmaterialtoggle_p.h"

#include <QApplication>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QStateMachine>

/*!
 *  \class QtMaterialTogglePrivate
 *  \internal
 */

QtMaterialTogglePrivate::QtMaterialTogglePrivate(QtMaterialToggle *q)
    : q_ptr(q)
{
}

QtMaterialTogglePrivate::~QtMaterialTogglePrivate()
{
}

void QtMaterialTogglePrivate::init()
{
    Q_Q(QtMaterialToggle);

    track = new QtMaterialToggleTrack(q);
    thumb = new QtMaterialToggleThumb(q);
    rippleOverlay = new QtMaterialToggleRippleOverlay(thumb, track, q);
    stateMachine = new QStateMachine(q);
    offState = new QState;
    onState = new QState;
    orientation = Qt::Horizontal;
    useThemeColors = true;

    q->setCheckable(true);
    q->setChecked(false);
    q->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    stateMachine->addState(offState);
    stateMachine->addState(onState);
    stateMachine->setInitialState(offState);

    offState->assignProperty(thumb, "shift", 0);
    onState->assignProperty(thumb, "shift", 1);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

    //

    transition = new QSignalTransition(q, &QtMaterialToggle::toggled);
    transition->setTargetState(onState);
    offState->addTransition(transition);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("shift");
    animation->setTargetObject(thumb);
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("trackColor");
    animation->setTargetObject(track);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("thumbColor");
    animation->setTargetObject(thumb);
    animation->setDuration(150);
    transition->addAnimation(animation);

    //

    transition = new QSignalTransition(q, &QtMaterialToggle::toggled);
    transition->setTargetState(offState);
    onState->addTransition(transition);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("shift");
    animation->setTargetObject(thumb);
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("trackColor");
    animation->setTargetObject(track);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("thumbColor");
    animation->setTargetObject(thumb);
    animation->setDuration(150);
    transition->addAnimation(animation);

    //

    setupProperties();

    stateMachine->start();
    QCoreApplication::processEvents();
}

void QtMaterialTogglePrivate::setupProperties()
{
    Q_Q(QtMaterialToggle);

    if (q->isEnabled())
    {
        const qreal shift = thumb->shift();
        if (qFuzzyCompare(shift, 1))
        {
            thumb->setThumbColor(q->activeColor());
            track->setTrackColor(q->activeColor().lighter(110));
        }
        else if (qFuzzyCompare(1 + shift, 1))
        {
            thumb->setThumbColor(q->inactiveColor());
            track->setTrackColor(q->trackColor());
        }
    }

    offState->assignProperty(track, "trackColor", q->trackColor().lighter(110));
    onState->assignProperty(track, "trackColor", q->activeColor().lighter(110));

    offState->assignProperty(thumb, "thumbColor", q->inactiveColor());
    onState->assignProperty(thumb, "thumbColor", q->activeColor());

    q->update();
}

/*!
 *  \class QtMaterialToggle
 */

QtMaterialToggle::QtMaterialToggle(QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new QtMaterialTogglePrivate(this))
{
    d_func()->init();
}

QtMaterialToggle::QtMaterialToggle(Qt::Orientation orientation, QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new QtMaterialTogglePrivate(this))
{
    d_func()->init();
    setOrientation(orientation);
}

QtMaterialToggle::~QtMaterialToggle()
{
}

void QtMaterialToggle::setUseThemeColors(bool value)
{
    Q_D(QtMaterialToggle);

    d->useThemeColors = value;
    d->setupProperties();
}

bool QtMaterialToggle::useThemeColors() const
{
    Q_D(const QtMaterialToggle);

    return d->useThemeColors;
}

void QtMaterialToggle::setDisabledColor(const QColor &color)
{
    Q_D(QtMaterialToggle);

    d->disabledColor = color;

    d->useThemeColors = false;
    d->setupProperties();
}

QColor QtMaterialToggle::disabledColor() const
{
    Q_D(const QtMaterialToggle);

    if (d->useThemeColors || !d->disabledColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeDisabled1);
    }

    return d->disabledColor;
}

void QtMaterialToggle::setActiveColor(const QColor &color)
{
    Q_D(QtMaterialToggle);

    d->activeColor = color;

    d->useThemeColors = false;
    d->setupProperties();
}

QColor QtMaterialToggle::activeColor() const
{
    Q_D(const QtMaterialToggle);

    if (d->useThemeColors || !d->activeColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemePrimaryMain);
    }

    return d->activeColor;
}

void QtMaterialToggle::setInactiveColor(const QColor &color)
{
    Q_D(QtMaterialToggle);

    d->inactiveColor = color;

    d->useThemeColors = false;
    d->setupProperties();
}

QColor QtMaterialToggle::inactiveColor() const
{
    Q_D(const QtMaterialToggle);

    if (d->useThemeColors || !d->inactiveColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeCanvas);
    }

    return d->inactiveColor;
}

void QtMaterialToggle::setTrackColor(const QColor &color)
{
    Q_D(QtMaterialToggle);

    d->trackColor = color;

    d->useThemeColors = false;
    d->setupProperties();
}

QColor QtMaterialToggle::trackColor() const
{
    Q_D(const QtMaterialToggle);

    if (d->useThemeColors || !d->trackColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeSecondaryDark);
    }

    return d->trackColor;
}

void QtMaterialToggle::setOrientation(Qt::Orientation orientation)
{
    Q_D(QtMaterialToggle);

    if (d->orientation == orientation)
    {
        return;
    }

    d->orientation = orientation;
    updateGeometry();
}

Qt::Orientation QtMaterialToggle::orientation() const
{
    Q_D(const QtMaterialToggle);

    return d->orientation;
}

QSize QtMaterialToggle::sizeHint() const
{
    Q_D(const QtMaterialToggle);

    return (d->orientation == Qt::Horizontal) ? QSize(64, 48) : QSize(48, 64);
}

bool QtMaterialToggle::event(QEvent *event)
{
    Q_D(QtMaterialToggle);

    switch (event->type())
    {
        case QEvent::ParentChange:
        {
            QWidget *widget;
            if ((widget = parentWidget()) != nullptr)
            {
                d->rippleOverlay->setParent(widget);
            }
            break;
        }
        default:
            break;
    }
    return QAbstractButton::event(event);
}

void QtMaterialToggle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
}
