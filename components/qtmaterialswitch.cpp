#include "qtmaterialswitch.h"

#include "lib/qtmaterialstyle.h"
#include "qtmaterialswitch_internal.h"
#include "qtmaterialswitch_p.h"

#include <QApplication>
#include <QPainter>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QStateMachine>

/*!
 *  \class QtMaterialSwitchPrivate
 *  \internal
 */

QtMaterialSwitchPrivate::QtMaterialSwitchPrivate(QtMaterialSwitch *q)
    : q_ptr(q)
{
}

QtMaterialSwitchPrivate::~QtMaterialSwitchPrivate()
{
}

void QtMaterialSwitchPrivate::init()
{
    Q_Q(QtMaterialSwitch);

    track = new QtMaterialSwitchTrack(q);
    thumb = new QtMaterialSwitchThumb(q);
    rippleOverlay = new QtMaterialSwitchRippleOverlay(thumb, track, q);
    stateMachine = new QStateMachine(q);
    offState = new QState;
    onState = new QState;
    orientation = Qt::Horizontal;
    useThemeColors = true;

    q->setFont(QtMaterialStyle::instance().themeFont(Material::FontBody1));

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

    transition = new QSignalTransition(q, &QtMaterialSwitch::toggled);
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

    transition = new QSignalTransition(q, &QtMaterialSwitch::toggled);
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

void QtMaterialSwitchPrivate::setupProperties()
{
    Q_Q(QtMaterialSwitch);

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
 *  \class QtMaterialSwitch
 */

QtMaterialSwitch::QtMaterialSwitch(QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new QtMaterialSwitchPrivate(this))
{
    d_func()->init();
}

QtMaterialSwitch::QtMaterialSwitch(Qt::Orientation orientation, QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new QtMaterialSwitchPrivate(this))
{
    d_func()->init();
    setOrientation(orientation);
}

QtMaterialSwitch::~QtMaterialSwitch()
{
}

void QtMaterialSwitch::setUseThemeColors(bool value)
{
    Q_D(QtMaterialSwitch);

    d->useThemeColors = value;
    d->setupProperties();
}

bool QtMaterialSwitch::useThemeColors() const
{
    Q_D(const QtMaterialSwitch);

    return d->useThemeColors;
}

void QtMaterialSwitch::setDisabledColor(const QColor &color)
{
    Q_D(QtMaterialSwitch);

    d->disabledColor = color;

    d->useThemeColors = false;
    d->setupProperties();
}

QColor QtMaterialSwitch::disabledColor() const
{
    Q_D(const QtMaterialSwitch);

    if (d->useThemeColors || !d->disabledColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeDisabled1);
    }

    return d->disabledColor;
}

void QtMaterialSwitch::setActiveColor(const QColor &color)
{
    Q_D(QtMaterialSwitch);

    d->activeColor = color;

    d->useThemeColors = false;
    d->setupProperties();
}

QColor QtMaterialSwitch::activeColor() const
{
    Q_D(const QtMaterialSwitch);

    if (d->useThemeColors || !d->activeColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemePrimaryMain);
    }

    return d->activeColor;
}

void QtMaterialSwitch::setInactiveColor(const QColor &color)
{
    Q_D(QtMaterialSwitch);

    d->inactiveColor = color;

    d->useThemeColors = false;
    d->setupProperties();
}

QColor QtMaterialSwitch::inactiveColor() const
{
    Q_D(const QtMaterialSwitch);

    if (d->useThemeColors || !d->inactiveColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeCanvas);
    }

    return d->inactiveColor;
}

QColor QtMaterialSwitch::trackColor() const
{
    Q_D(const QtMaterialSwitch);

    if (d->useThemeColors || !d->trackColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeSecondaryDark);
    }

    return d->trackColor;
}

void QtMaterialSwitch::setTrackColor(const QColor &color)
{
    Q_D(QtMaterialSwitch);

    d->trackColor = color;

    d->useThemeColors = false;
    d->setupProperties();
}

QColor QtMaterialSwitch::textColor() const
{
    Q_D(const QtMaterialSwitch);

    if (d->useThemeColors || !d->textColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeText);
    }

    return d->textColor;
}

void QtMaterialSwitch::setTextColor(const QColor &color)
{
    Q_D(QtMaterialSwitch);

    d->textColor = color;

    d->useThemeColors = false;
    update();
}

void QtMaterialSwitch::setOrientation(Qt::Orientation orientation)
{
    Q_D(QtMaterialSwitch);

    if (d->orientation == orientation)
    {
        return;
    }

    d->orientation = orientation;
    updateGeometry();
}

Qt::Orientation QtMaterialSwitch::orientation() const
{
    Q_D(const QtMaterialSwitch);

    return d->orientation;
}

QSize QtMaterialSwitch::sizeHint() const
{
    Q_D(const QtMaterialSwitch);

    QSize textSize(fontMetrics().size(Qt::TextSingleLine | Qt::TextShowMnemonic, text()));

    if (d->orientation == Qt::Horizontal)
    {
        return QSize(64 + textSize.width(), 48);
    }
    else
    {
        return QSize(48 + textSize.width(), 64);
    }
}

bool QtMaterialSwitch::event(QEvent *event)
{
    Q_D(QtMaterialSwitch);

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
        case QEvent::StyleChange:
        {
            d->setupProperties();
            break;
        }
        case QEvent::Move:
        case QEvent::Resize:
        {
            QRect switchGeometry;
            if (d->orientation == Qt::Horizontal)
            {
                switchGeometry = QRect(0, 0, 64, 48);
            }
            else
            {
                switchGeometry = QRect(0, 0, 48, 64);
            }
            d->thumb->setGeometry(switchGeometry.adjusted(8, 8, -8, -8));
            d->track->setGeometry(switchGeometry);
            break;
        }
        default:
        {
            break;
        }
    }
    return QAbstractButton::event(event);
}

void QtMaterialSwitch::paintEvent(QPaintEvent *event)
{
    Q_D(QtMaterialSwitch);

    Q_UNUSED(event)

    QPainter painter(this);

    QPen pen;
    pen.setColor(isEnabled() ? textColor() : disabledColor());
    painter.setPen(pen);

    int heightText = fontMetrics().height();
    int yText = (height() - heightText) / 2 + heightText - fontMetrics().descent();
    int xText = (d->orientation == Qt::Horizontal) ? 64 : 48;
    painter.drawText(xText, yText, text());
}
