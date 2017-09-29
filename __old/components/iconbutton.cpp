#include "iconbutton.h"
#include "iconbutton_p.h"
#include <QPainter>
#include <QEvent>
#include "lib/style.h"
#include "lib/rippleoverlay.h"

IconButtonPrivate::IconButtonPrivate(IconButton *q)
    : q_ptr(q),
      ripple(new RippleOverlay(q->parentWidget()))
{
}

void IconButtonPrivate::init()
{
    Q_Q(IconButton);

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
    Q_D(IconButton);

    switch (event->type())
    {
    case QEvent::Resize:
    case QEvent::Move: {
        const int s = iconSize().width()/2;
        d->ripple->setGeometry(geometry().adjusted(-s, -s, s, s));
        break;
    }
    case QEvent::ParentChange: {
        QWidget *widget;
        if ((widget = parentWidget())) {
            d->ripple->setParent(widget);
        }
        break;
    }
    default:
        break;
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
