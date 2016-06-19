#include "textfield.h"
#include <QPainter>
#include <QPaintEvent>
#include <QApplication>
#include "textfield_p.h"
#include "textfield_internal.h"
#include "lib/style.h"

TextFieldPrivate::TextFieldPrivate(TextField *q)
    : q_ptr(q),
      label(0),
      labelFontSize(9.5),
      showLabel(false),
      useThemeColors(true)
{
    q->setFrame(false);
}

void TextFieldPrivate::init()
{
    Q_Q(TextField);

    q->setTextMargins(0, 2, 0, 0);

    machine = new TextFieldStateMachine(q);
    machine->start();

    QCoreApplication::processEvents();
}

TextField::TextField(QWidget *parent)
    : QLineEdit(parent),
      d_ptr(new TextFieldPrivate(this))
{
    d_func()->init();
}

TextField::~TextField()
{
}

void TextField::setUseThemeColors(bool value)
{
    Q_D(TextField);

    d->useThemeColors = value;
    d->machine->assignProperties();
}

bool TextField::useThemeColors() const
{
    Q_D(const TextField);

    return d->useThemeColors;
}

void TextField::setShowLabel(bool value)
{
    Q_D(TextField);

    if (!d->label) {
        d->label = new TextFieldLabel(this);
        d->machine->setLabel(d->label);
    }

    d->showLabel = value;

    if (value) {
        setContentsMargins(0, 23, 0, 0);
    } else {
        setContentsMargins(0, 0, 0, 0);
    }
}

bool TextField::hasLabel() const
{
    Q_D(const TextField);

    return d->showLabel;
}

void TextField::setLabelFontSize(qreal size)
{
    Q_D(TextField);

    d->labelFontSize = size;

    if (d->label) {
        QFont f(d->label->font());
        f.setPointSizeF(size);
        d->label->setFont(f);
    }
}

qreal TextField::labelFontSize() const
{
    Q_D(const TextField);

    return d->labelFontSize;
}

void TextField::setLabel(const QString &label)
{
    Q_D(TextField);

    d->labelString = label;
    setShowLabel(true);
}

QString TextField::label() const
{
    Q_D(const TextField);

    return d->labelString;
}

void TextField::setTextColor(const QColor &color)
{
    Q_D(TextField);

    d->textColor = color;
    setUseThemeColors(false);
}

QColor TextField::textColor() const
{
    Q_D(const TextField);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return Style::instance().themeColor("text");
    } else {
        return d->textColor;
    }
}

void TextField::setBackgroundColor(const QColor &color)
{
    Q_D(TextField);

    d->backgroundColor = color;
    setUseThemeColors(false);
}

QColor TextField::backgroundColor() const
{
    Q_D(const TextField);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return palette().color(QPalette::Window);
    } else {
        return d->backgroundColor;
    }
}

void TextField::setInkColor(const QColor &color)
{
    Q_D(TextField);

    d->inkColor = color;
    setUseThemeColors(false);
}

QColor TextField::inkColor() const
{
    Q_D(const TextField);

    if (d->useThemeColors || !d->inkColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->inkColor;
    }
}

void TextField::setUnderlineColor(const QColor &color)
{
    Q_D(TextField);

    d->underlineColor = color;
    setUseThemeColors(false);
}

QColor TextField::underlineColor() const
{
    Q_D(const TextField);

    if (d->useThemeColors || !d->underlineColor.isValid()) {
        return Style::instance().themeColor("border");
    } else {
        return d->underlineColor;
    }
}

void TextField::setHintColor(const QColor &color)
{
    Q_D(TextField);

    d->hintColor = color;
    setUseThemeColors(false);
}

QColor TextField::hintColor() const
{
    Q_D(const TextField);

    if (d->useThemeColors || !d->hintColor.isValid()) {
        return Style::instance().themeColor("accent3");
    } else {
        return d->hintColor;
    }
}

bool TextField::event(QEvent *event)
{
    Q_D(TextField);

    switch (event->type())
    {
    case QEvent::Resize:
    case QEvent::Move: {
        if (d->label) {
            d->label->setGeometry(rect());
        }
    }
    default:
        break;
    }
    return QLineEdit::event(event);
}

void TextField::paintEvent(QPaintEvent *event)
{
    Q_D(TextField);

    QLineEdit::paintEvent(event);

    QPainter painter(this);

    if (text().isEmpty())
    {
        QBrush bgBrush;
        bgBrush.setStyle(Qt::SolidPattern);
        bgBrush.setColor(backgroundColor());
        painter.setOpacity(1-d->machine->progress());
        painter.fillRect(rect(), bgBrush);
    }

    const int y = height()-1;
    const int wd = width()-5;

    QPen pen;
    pen.setWidth(1);
    pen.setColor(underlineColor());
    painter.setPen(pen);
    painter.setOpacity(1);
    painter.drawLine(2.5, y, wd, y);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(inkColor());

    const qreal progress = d->machine->progress();

    if (progress > 0)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(brush);

        int w = (1-progress)*static_cast<qreal>(wd/2);
        painter.drawRect(w+2.5, height()-2, wd-w*2, 2);
    }
}
