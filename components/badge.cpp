#include "badge.h"
#include <QPainter>
#include <QIcon>
#include "badge_p.h"
#include "lib/style.h"

BadgePrivate::BadgePrivate(Badge *q)
    : q_ptr(q),
      padding(10)
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
}

Badge::Badge(QWidget *parent)
    : QWidget(parent),
      d_ptr(new BadgePrivate(this))
{
    d_func()->init();
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

QSize Badge::sizeHint() const
{
    const int s = getDiameter();
    return QSize(s, s);
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

    QFontMetrics fm = fontMetrics();
    d->size = fm.size(Qt::TextShowMnemonic, text);

    update();
}

void Badge::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(Badge);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

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
