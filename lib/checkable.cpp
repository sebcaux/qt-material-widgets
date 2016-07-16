#include "checkable.h"
#include "checkable_p.h"
#include <QPainter>
#include <QEvent>
#include <QStateMachine>
#include <QSignalTransition>
#include <QEventTransition>
#include <QApplication>
#include <QFontDatabase>
#include <QDebug>
#include "lib/rippleoverlay.h"
#include "xxlib/qtmaterialstyle.h"
#include "lib/ripple.h"

CheckablePrivate::CheckablePrivate(Checkable *q)
    : q_ptr(q),
      ripple(new RippleOverlay),
      checkedIcon(new CheckableIcon(QIcon("../qt-material-widgets/ic_check_box_black_24px.svg"))),
      uncheckedIcon(new CheckableIcon(QIcon("../qt-material-widgets/ic_check_box_outline_blank_black_24px.svg"))),
      machine(new QStateMachine),
      uncheckedState(new QState),
      checkedState(new QState),
      disabledUncheckedState(new QState),
      disabledCheckedState(new QState),
      uncheckedTransition(new QSignalTransition(q, SIGNAL(toggled(bool)))),
      checkedTransition(new QSignalTransition(q, SIGNAL(toggled(bool)))),
      useThemeColors(true)
{
}

CheckablePrivate::~CheckablePrivate()
{
}

void CheckablePrivate::init()
{
    Q_Q(Checkable);

    q->setCheckable(true);

    uncheckedIcon->setParent(q);
    checkedIcon->setParent(q);

    //QFont f(q->font());
    //f.setPointSizeF(11);
    //q->setFont(f);

    q->setStyle(&QtMaterialStyle::instance());

    QFontDatabase db;
    QFont font(db.font("Roboto", "Medium", 11));
    q->setFont(font);

    //

    ripple->setParent(q->parentWidget());
    machine->setParent(q);

    machine->addState(uncheckedState);
    machine->addState(checkedState);
    machine->addState(disabledUncheckedState);
    machine->addState(disabledCheckedState);

    machine->setInitialState(uncheckedState);

    // Transition to checked

    uncheckedTransition->setTargetState(checkedState);
    uncheckedState->addTransition(uncheckedTransition);

    // Transition to unchecked

    checkedTransition->setTargetState(uncheckedState);
    checkedState->addTransition(checkedTransition);

    QAbstractTransition *transition;

    // Enabled-Disabled transitions

    transition = new QEventTransition(q, QEvent::EnabledChange);
    transition->setTargetState(disabledUncheckedState);
    uncheckedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::EnabledChange);
    transition->setTargetState(uncheckedState);
    disabledUncheckedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::EnabledChange);
    transition->setTargetState(disabledCheckedState);
    checkedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::EnabledChange);
    transition->setTargetState(checkedState);
    disabledCheckedState->addTransition(transition);

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(disabledCheckedState);
    disabledUncheckedState->addTransition(transition);

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(disabledUncheckedState);
    disabledCheckedState->addTransition(transition);
}

Checkable::Checkable(QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new CheckablePrivate(this))
{
    d_func()->init();
}

Checkable::~Checkable()
{
}

void Checkable::setUseThemeColors(bool state)
{
    Q_D(Checkable);

    d->useThemeColors = state;
    assignProperties();
    update();
}

bool Checkable::useThemeColors() const
{
    Q_D(const Checkable);

    return d->useThemeColors;
}

void Checkable::setCheckedColor(const QColor &color)
{
    Q_D(Checkable);

    d->checkedColor = color;
    setUseThemeColors(false);
}

QColor Checkable::checkedColor() const
{
    Q_D(const Checkable);

    if (d->useThemeColors || !d->checkedColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    } else {
        return d->checkedColor;
    }
}

void Checkable::setUncheckedColor(const QColor &color)
{
    Q_D(Checkable);

    d->uncheckedColor = color;
    setUseThemeColors(false);
}

QColor Checkable::uncheckedColor() const
{
    Q_D(const Checkable);

    if (d->useThemeColors || !d->uncheckedColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    } else {
        return d->uncheckedColor;
    }
}

void Checkable::setTextColor(const QColor &color)
{
    Q_D(Checkable);

    d->textColor = color;
    setUseThemeColors(false);
}

QColor Checkable::textColor() const
{
    Q_D(const Checkable);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    } else {
        return d->textColor;
    }
}

void Checkable::setDisabledColor(const QColor &color)
{
    Q_D(Checkable);

    d->disabledColor = color;
    setUseThemeColors(false);
}

QColor Checkable::disabledColor() const
{
    Q_D(const Checkable);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        // Transparency will not work here, since we use this color to
        // tint the icon using a QGraphicsColorizeEffect
        return QtMaterialStyle::instance().themeColor("accent3");
    } else {
        return d->disabledColor;
    }
}

void Checkable::setCheckedIcon(const QIcon &icon)
{
    Q_D(Checkable);

    d->checkedIcon->setIcon(icon);
}

QIcon Checkable::checkedIcon() const
{
    Q_D(const Checkable);

    return d->checkedIcon->icon();
}

void Checkable::setUncheckedIcon(const QIcon &icon)
{
    Q_D(Checkable);

    d->uncheckedIcon->setIcon(icon);
}

QIcon Checkable::uncheckedIcon() const
{
    Q_D(const Checkable);

    return d->uncheckedIcon->icon();
}

QSize Checkable::sizeHint() const
{
    QString s(text());
    //if (s.isEmpty())
    //    return QSize(32, 32);
    if (s.isEmpty())
        return QSize(40, 40);

    QFontMetrics fm = fontMetrics();
    QSize sz = fm.size(Qt::TextShowMnemonic, s);

    //return QSize(sz.width() + 44, 32);
    return QSize(sz.width() + 52, 40);
}

Checkable::Checkable(CheckablePrivate &d, QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(&d)
{
    d_func()->init();
}

bool Checkable::event(QEvent *event)
{
    Q_D(Checkable);

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
    default:
        break;
    }
    return QAbstractButton::event(event);
}

void Checkable::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if (!isEnabled())
        return;

    Q_D(Checkable);

    //Ripple *ripple = new Ripple(QPoint(28, 28));
    Ripple *ripple = new Ripple(QPoint(width()-14, 28));
    ripple->setRadiusEndValue(22);
    ripple->setColor(isChecked() ? checkedColor() : uncheckedColor());
    if (isChecked()) {
        ripple->setOpacityStartValue(1);
    }
    d->ripple->addRipple(ripple);

    setChecked(!isChecked());
}

void Checkable::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QPen pen;
    pen.setColor(isEnabled() ? textColor() : disabledColor());
    painter.setPen(pen);

    /*
    painter.drawText(44, 25, text());
    */

    painter.drawText(0, 25, text());
}

void Checkable::assignProperties()
{
}
