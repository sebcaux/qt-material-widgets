#include "iconbutton.h"
#include <QPainter>
#include <QEvent>
#include "iconbutton_p.h"
#include "lib/style.h"
#include "lib/rippleoverlay.h"

IconButtonPrivate::IconButtonPrivate(IconButton *q)
    : q_ptr(q)
{
}

void IconButtonPrivate::init()
{
    Q_Q(IconButton);

    ripple = new RippleOverlay(q);

    QSizePolicy policy;
    policy.setWidthForHeight(true);
    q->setSizePolicy(policy);
}

IconButton::IconButton(const QIcon &icon, QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new IconButtonPrivate(this))
{
    d_func()->init();

    setIcon(icon);
}

IconButton::~IconButton()
{
}

QSize IconButton::sizeHint() const
{
    return iconSize();
}

bool IconButton::event(QEvent *event)
{
    const QEvent::Type type = event->type();
    if (QEvent::Resize == type || QEvent::Move == type)
    {
        Q_D(IconButton);

        const int s = iconSize().width()/2;
        d->ripple->setGeometry(geometry().adjusted(-s, -s, s, s));
    }
    else if (QEvent::ParentChange == type && parentWidget())
    {
        Q_D(IconButton);

        d->ripple->setParent(parentWidget());
    }
    return QAbstractButton::event(event);
}

void IconButton::mousePressEvent(QMouseEvent *event)
{
    Q_D(IconButton);

    const QPoint p(d->ripple->width(), d->ripple->height());
    d->ripple->addRipple(p/2, iconSize().width());

    emit clicked();

    QAbstractButton::mousePressEvent(event);
}

void IconButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    const QSize &size = iconSize();
    QPoint pos(width()/2-size.width()/2, height()/2-size.height()/2);
    icon().paint(&painter, QRect(pos, size), Qt::AlignCenter,
        isEnabled() ? QIcon::Normal
                    : QIcon::Disabled);
}
