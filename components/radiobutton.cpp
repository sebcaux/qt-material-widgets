#include "radiobutton.h"
#include <QPainter>
#include <QEvent>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QApplication>
#include <QDebug>
#include "radiobutton_p.h"
#include "lib/rippleoverlay.h"
#include "lib/style.h"
#include "lib/ripple.h"

RadioButtonPrivate::RadioButtonPrivate(RadioButton *q)
    : q_ptr(q),
      checkedIcon(new RadioButtonIcon(QIcon("../qt-material-widgets/ic_radio_button_checked_black_24px.svg"))),
      uncheckedIcon(new RadioButtonIcon(QIcon("../qt-material-widgets/ic_radio_button_unchecked_black_24px.svg"))),
      iconSize(24),
      useThemeColors(true)
{
}

void RadioButtonPrivate::init()
{
    Q_Q(RadioButton);

    checkedIcon->setParent(q);
    uncheckedIcon->setParent(q);

    ripple = new RippleOverlay(q->parentWidget());
    machine = new QStateMachine(q);

    QFont f(q->font());
    f.setPointSizeF(11);
    q->setFont(f);

    uncheckedState = new QState;
    checkedState = new QState;

    machine->addState(uncheckedState);
    machine->addState(checkedState);

    machine->setInitialState(uncheckedState);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(checkedState);
    uncheckedState->addTransition(transition);

    animation = new QPropertyAnimation(checkedIcon, "iconSize");
    animation->setDuration(250);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "iconSize");
    animation->setDuration(250);
    transition->addAnimation(animation);

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(uncheckedState);
    checkedState->addTransition(transition);

    animation = new QPropertyAnimation(checkedIcon, "iconSize");
    animation->setDuration(250);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "iconSize");
    animation->setDuration(250);
    transition->addAnimation(animation);

    assignAnimationProperties();
    updatePalette();

    machine->start();

    QCoreApplication::processEvents();
}

void RadioButtonPrivate::assignAnimationProperties()
{
    uncheckedState->assignProperty(checkedIcon, "iconSize", 0);
    uncheckedState->assignProperty(uncheckedIcon, "iconSize", iconSize);

    checkedState->assignProperty(uncheckedIcon, "iconSize", 0);
    checkedState->assignProperty(checkedIcon, "iconSize", iconSize);
}

void RadioButtonPrivate::updatePalette()
{
    Q_Q(RadioButton);

    if (q->isEnabled()) {
        checkedIcon->setColor(q->checkedColor());
        uncheckedIcon->setColor(q->uncheckedColor());
    } else {
        checkedIcon->setColor(q->disabledColor());
        uncheckedIcon->setColor(q->disabledColor());
    }
}

RadioButton::RadioButton(QWidget *parent)
    : QRadioButton(parent),
      d_ptr(new RadioButtonPrivate(this))
{
    d_func()->init();
}

RadioButton::~RadioButton()
{
}

void RadioButton::setUseThemeColors(bool state)
{
    Q_D(RadioButton);

    d->useThemeColors = state;
    d->updatePalette();
    update();
}

bool RadioButton::useThemeColors() const
{
    Q_D(const RadioButton);

    return d->useThemeColors;
}

void RadioButton::setCheckedColor(const QColor &color)
{
    Q_D(RadioButton);

    d->checkedColor = color;
    setUseThemeColors(false);
}

QColor RadioButton::checkedColor() const
{
    Q_D(const RadioButton);

    if (d->useThemeColors || !d->checkedColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->checkedColor;
    }
}

void RadioButton::setUncheckedColor(const QColor &color)
{
    Q_D(RadioButton);

    d->uncheckedColor = color;
    setUseThemeColors(false);
}

QColor RadioButton::uncheckedColor() const
{
    Q_D(const RadioButton);

    if (d->useThemeColors || !d->uncheckedColor.isValid()) {
        return Style::instance().themeColor("text");
    } else {
        return d->uncheckedColor;
    }
}

void RadioButton::setTextColor(const QColor &color)
{
    Q_D(RadioButton);

    d->textColor = color;
    setUseThemeColors(false);
}

QColor RadioButton::textColor() const
{
    Q_D(const RadioButton);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return Style::instance().themeColor("text");
    } else {
        return d->textColor;
    }
}

void RadioButton::setDisabledColor(const QColor &color)
{
    Q_D(RadioButton);

    d->disabledColor = color;
    setUseThemeColors(false);
}

QColor RadioButton::disabledColor() const
{
    Q_D(const RadioButton);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        // Transparency will not work here, since we use this color to
        // tint the icon using a QGraphicsColorizeEffect
        return Style::instance().themeColor("accent3");
    } else {
        return d->disabledColor;
    }
}

void RadioButton::setCheckedIcon(const QIcon &icon)
{
    Q_D(RadioButton);

    d->checkedIcon->setIcon(icon);
}

QIcon RadioButton::checkedIcon() const
{
    Q_D(const RadioButton);

    return d->checkedIcon->icon();
}

void RadioButton::setUncheckedIcon(const QIcon &icon)
{
    Q_D(RadioButton);

    d->uncheckedIcon->setIcon(icon);
}

QIcon RadioButton::uncheckedIcon() const
{
    Q_D(const RadioButton);

    return d->uncheckedIcon->icon();
}

void RadioButton::setIconSize(int size)
{
    Q_D(RadioButton);

    if (size > 38) {
        size = 38;
        qWarning() << "RadioButton::setIconSize: maximum allowed icon size is 38";
    }

    d->iconSize = size;
    d->assignAnimationProperties();

    if (isChecked()) {
        d->checkedIcon->setIconSize(size);
    } else {
        d->uncheckedIcon->setIconSize(size);
    }
    update();
}

int RadioButton::iconSize() const
{
    Q_D(const RadioButton);

    return d->iconSize;
}

QSize RadioButton::sizeHint() const
{
    QString s(text());
    if (s.isEmpty())
        return QSize(32, 32);

    QFontMetrics fm = fontMetrics();
    QSize sz = fm.size(Qt::TextShowMnemonic, s);

    return QSize(sz.width() + 44, 32);
}

bool RadioButton::event(QEvent *event)
{
    Q_D(RadioButton);

    switch (event->type())
    {
    case QEvent::Resize:
    case QEvent::Move:
        d->ripple->setGeometry(geometry().adjusted(-8, -8, 8, 8));
        d->checkedIcon->setGeometry(rect());
        d->uncheckedIcon->setGeometry(rect());
        break;
    case QEvent::ParentChange:
        QWidget *widget;
        if ((widget = parentWidget())) {
            d->ripple->setParent(widget);
        }
        break;
    case QEvent::EnabledChange:
        d->updatePalette();
        if (isChecked()) {
            d->checkedIcon->setIconSize(d->iconSize);
            d->uncheckedIcon->setIconSize(0);
        } else {
            d->checkedIcon->setIconSize(0);
            d->uncheckedIcon->setIconSize(d->iconSize);
        }
        break;
    default:
        break;
    }
    return QRadioButton::event(event);
}

void RadioButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if (!isEnabled())
        return;

    Q_D(RadioButton);

    Ripple *ripple = new Ripple(QPoint(24, 24));
    ripple->setRadiusEndValue(24);
    ripple->setColor(isChecked() ? d->checkedIcon->color() : Qt::black);
    d->ripple->addRipple(ripple);

    setChecked(!isChecked());
}

void RadioButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QPen pen;
    pen.setColor(isEnabled() ? textColor() : disabledColor());
    painter.setPen(pen);

    painter.drawText(44, 21, text());
}
