#include "badge.h"
#include "badge_p.h"
#include <QPainter>
#include <QIcon>
#include <QEvent>
#include <QDebug>
#include "lib/style.h"

BadgePrivate::BadgePrivate(Badge *q)
    : q_ptr(q),
      padding(10),
      useThemeColors(true),
      x(0),
      y(0)
{
}

BadgePrivate::~BadgePrivate()
{
}

void BadgePrivate::init()
{
    Q_Q(Badge);

    q->setAttribute(Qt::WA_TransparentForMouseEvents);

    QFont font(q->font());
    font.setPointSizeF(10);
    font.setStyleName("Medium");
    q->setFont(font);

    q->setText("+1");

    if (q->parentWidget()) {
        q->parentWidget()->installEventFilter(q);
    }
}

Badge::Badge(QWidget *parent)
    : QWidget(parent),
      d_ptr(new BadgePrivate(this))
{
    d_func()->init();
}

Badge::Badge(const QIcon &icon, QWidget *parent)
    : QWidget(parent),
      d_ptr(new BadgePrivate(this))
{
    d_func()->init();

    setIcon(icon);
}

Badge::Badge(const QString &text, QWidget *parent)
    : QWidget(parent),
      d_ptr(new BadgePrivate(this))
{
    d_func()->init();

    setText(text);
}

Badge::~Badge()
{
}

void Badge::setUseThemeColors(bool value)
{
    Q_D(Badge);

    d->useThemeColors = value;
}

bool Badge::useThemeColors() const
{
    Q_D(const Badge);

    return d->useThemeColors;
}

void Badge::setTextColor(const QColor &color)
{
    Q_D(Badge);

    d->textColor = color;
    setUseThemeColors(false);
}

QColor Badge::textColor() const
{
    Q_D(const Badge);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return Style::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void Badge::setBackgroundColor(const QColor &color)
{
    Q_D(Badge);

    d->backgroundColor = color;
    setUseThemeColors(false);
}

QColor Badge::backgroundColor() const
{
    Q_D(const Badge);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return Style::instance().themeColor("accent1");
    } else {
        return d->backgroundColor;
    }
}

void Badge::setRelativePosition(const QPointF &pos)
{
    setRelativePosition(pos.x(), pos.y());
}

void Badge::setRelativePosition(qreal x, qreal y)
{
    Q_D(Badge);

    d->x = x;
    d->y = y;
    update();
}

QPointF Badge::relativePosition() const
{
    Q_D(const Badge);

    return QPointF(d->x, d->y);
}

void Badge::setRelativeXPosition(qreal x)
{
    Q_D(Badge);

    d->x = x;
    update();
}

qreal Badge::relativeXPosition() const
{
    Q_D(const Badge);

    return d->x;
}

void Badge::setRelativeYPosition(qreal y)
{
    Q_D(Badge);

    d->y = y;
    update();
}

qreal Badge::relativeYPosition() const
{
    Q_D(const Badge);

    return d->y;
}

QSize Badge::sizeHint() const
{
    const int s = getDiameter();
    return QSize(s+4, s+4);
}

void Badge::setIcon(const QIcon &icon)
{
    Q_D(Badge);

    d->icon = icon;
    update();
}

void Badge::setText(const QString &text)
{
    Q_D(Badge);

    d->text = text;

    if (!d->icon.isNull()) {
        d->icon = QIcon();
    }

    d->size = fontMetrics().size(Qt::TextShowMnemonic, text);

    update();
}

bool Badge::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::ParentChange:
    {
        if (!parent())
            break;

        parent()->installEventFilter(this);

        QWidget *widget;
        if ((widget = parentWidget())) {
            setGeometry(widget->rect());
        }
        break;
    }
    case QEvent::ParentAboutToChange:
    {
        if (!parent())
            break;

        parent()->removeEventFilter(this);
        break;
    }
    default:
        break;
    }
    return QWidget::event(event);
}

bool Badge::eventFilter(QObject *obj, QEvent *event)
{
    QEvent::Type type = event->type();

    if (QEvent::Move == type || QEvent::Resize == type)
    {
        QWidget *widget;
        if ((widget = parentWidget())) {
            setGeometry(widget->rect());
        }
    }
    return QWidget::eventFilter(obj, event);
}

void Badge::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(Badge);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.translate(d->x, d->y);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(backgroundColor());
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    const int s = getDiameter();

    QRectF r(0, 0, s, s);
    r.translate(QPointF((width()-s), (height()-s))/2);

    if (d->icon.isNull())
    {
        painter.drawEllipse(r.translated(0, 0.5));

        painter.setPen(textColor());
        painter.setBrush(Qt::NoBrush);
        painter.drawText(r, Qt::AlignCenter, d->text);
    }
    else
    {
        painter.drawEllipse(r);

        QRectF q(0, 0, 16, 16);
        q.moveCenter(r.center());
        d->icon.paint(&painter, q.toRect(), Qt::AlignCenter);
    }
}

int Badge::getDiameter() const
{
    Q_D(const Badge);

    if (d->icon.isNull()) {
        return qMax(d->size.width(), d->size.height()) + d->padding;
    } else {
        return 24;
    }
}
