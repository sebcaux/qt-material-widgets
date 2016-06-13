#include "checkbox.h"
#include <QPainter>
#include <QEvent>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QApplication>
#include <QDebug>
#include "checkbox_p.h"
#include "lib/rippleoverlay.h"
#include "lib/style.h"
#include "lib/ripple.h"

CheckboxPrivate::CheckboxPrivate(Checkbox *q)
    : q_ptr(q),
      checkedIcon(new CheckboxIcon(QIcon("../qt-material-widgets/ic_check_box_black_24px.svg"))),
      uncheckedIcon(new CheckboxIcon(QIcon("../qt-material-widgets/ic_check_box_outline_blank_black_24px.svg"))),
      iconSize(24),
      useThemeColors(true)
{
}

void CheckboxPrivate::init()
{
    Q_Q(Checkbox);

    q->setCheckable(true);

    uncheckedIcon->setParent(q);
    checkedIcon->setParent(q);

    ripple = new RippleOverlay(q->parentWidget());
    machine = new QStateMachine(q);

    QFont f(q->font());
    f.setPointSizeF(11);
    q->setFont(f);

    uncheckedState = new QState;
    transitionState = new QState;
    checkedState = new QState;

    machine->addState(uncheckedState);
    machine->addState(transitionState);
    machine->addState(checkedState);

    machine->setInitialState(uncheckedState);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(transitionState);
    uncheckedState->addTransition(transition);

    transition = new QSignalTransition(transitionState, SIGNAL(propertiesAssigned()));
    transition->setTargetState(checkedState);
    transitionState->addTransition(transition);

    animation = new QPropertyAnimation(checkedIcon, "iconSize");
    animation->setDuration(250);
    transition->addAnimation(animation);

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(uncheckedState);
    checkedState->addTransition(transition);

    animation = new QPropertyAnimation(checkedIcon, "opacity");
    animation->setDuration(350);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(checkedIcon, "iconSize");
    animation->setDuration(1250);
    transition->addAnimation(animation);

    q->assignAnimationProperties();
    updatePalette();

    machine->start();

    QCoreApplication::processEvents();
}

void CheckboxPrivate::updatePalette()
{
    Q_Q(Checkbox);

    if (q->isEnabled()) {
        checkedIcon->setColor(q->checkedColor());
        uncheckedIcon->setColor(q->uncheckedColor());
    } else {
        checkedIcon->setColor(q->disabledColor());
        uncheckedIcon->setColor(q->disabledColor());
    }
}

Checkbox::Checkbox(QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new CheckboxPrivate(this))
{
    d_func()->init();
}

Checkbox::~Checkbox()
{
}

void Checkbox::setUseThemeColors(bool state)
{
    Q_D(Checkbox);

    d->useThemeColors = state;
    d->updatePalette();
    update();
}

bool Checkbox::useThemeColors() const
{
    Q_D(const Checkbox);

    return d->useThemeColors;
}

void Checkbox::setCheckedColor(const QColor &color)
{
    Q_D(Checkbox);

    d->checkedColor = color;
    setUseThemeColors(false);
}

QColor Checkbox::checkedColor() const
{
    Q_D(const Checkbox);

    if (d->useThemeColors || !d->checkedColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->checkedColor;
    }
}

void Checkbox::setUncheckedColor(const QColor &color)
{
    Q_D(Checkbox);

    d->uncheckedColor = color;
    setUseThemeColors(false);
}

QColor Checkbox::uncheckedColor() const
{
    Q_D(const Checkbox);

    if (d->useThemeColors || !d->uncheckedColor.isValid()) {
        return Style::instance().themeColor("text");
    } else {
        return d->uncheckedColor;
    }
}

void Checkbox::setTextColor(const QColor &color)
{
    Q_D(Checkbox);

    d->textColor = color;
    setUseThemeColors(false);
}

QColor Checkbox::textColor() const
{
    Q_D(const Checkbox);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return Style::instance().themeColor("text");
    } else {
        return d->textColor;
    }
}

void Checkbox::setDisabledColor(const QColor &color)
{
    Q_D(Checkbox);

    d->disabledColor = color;
    setUseThemeColors(false);
}

QColor Checkbox::disabledColor() const
{
    Q_D(const Checkbox);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        // Transparency will not work here, since we use this color to
        // tint the icon using a QGraphicsColorizeEffect
        return Style::instance().themeColor("accent3");
    } else {
        return d->disabledColor;
    }
}

void Checkbox::setCheckedIcon(const QIcon &icon)
{
    Q_D(Checkbox);

    d->checkedIcon->setIcon(icon);
}

QIcon Checkbox::checkedIcon() const
{
    Q_D(const Checkbox);

    return d->checkedIcon->icon();
}

void Checkbox::setUncheckedIcon(const QIcon &icon)
{
    Q_D(Checkbox);

    d->uncheckedIcon->setIcon(icon);
}

QIcon Checkbox::uncheckedIcon() const
{
    Q_D(const Checkbox);

    return d->uncheckedIcon->icon();
}

void Checkbox::setIconSize(int size)
{
    Q_D(Checkbox);

    if (size > 38) {
        size = 38;
        qWarning() << "Checkbox::setIconSize: maximum allowed icon size is 38";
    }

    d->iconSize = size;
    assignAnimationProperties();

    if (isChecked()) {
        d->checkedIcon->setIconSize(size);
        d->uncheckedIcon->setIconSize(0);
    } else {
        d->uncheckedIcon->setIconSize(size);
        d->checkedIcon->setIconSize(0);
    }
    update();
}

int Checkbox::iconSize() const
{
    Q_D(const Checkbox);

    return d->iconSize;
}

QSize Checkbox::sizeHint() const
{
    QString s(text());
    if (s.isEmpty())
        return QSize(32, 32);

    QFontMetrics fm = fontMetrics();
    QSize sz = fm.size(Qt::TextShowMnemonic, s);

    return QSize(sz.width() + 44, 32);
}

bool Checkbox::event(QEvent *event)
{
    Q_D(Checkbox);

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
    return QAbstractButton::event(event);
}

void Checkbox::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if (!isEnabled())
        return;

    Q_D(Checkbox);

    Ripple *ripple = new Ripple(QPoint(24, 24));
    ripple->setRadiusEndValue(24);
    ripple->setColor(isChecked() ? d->checkedIcon->color() : Qt::black);
    d->ripple->addRipple(ripple);

    setChecked(!isChecked());
}

void Checkbox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QPen pen;
    pen.setColor(isEnabled() ? textColor() : disabledColor());
    painter.setPen(pen);

    painter.drawText(44, 21, text());
}

void Checkbox::assignAnimationProperties()
{
    Q_D(Checkbox);

    d->uncheckedState->assignProperty(d->checkedIcon, "opacity", 0);
    d->uncheckedState->assignProperty(d->checkedIcon, "iconSize", d->iconSize);
    d->uncheckedState->assignProperty(d->uncheckedIcon, "color", uncheckedColor());

    d->transitionState->assignProperty(d->checkedIcon, "iconSize", 0);

    d->checkedState->assignProperty(d->checkedIcon, "opacity", 1);
    d->checkedState->assignProperty(d->checkedIcon, "iconSize", d->iconSize);
    d->checkedState->assignProperty(d->uncheckedIcon, "color", checkedColor());
}
