#include "fab.h"
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include "fab_p.h"

FloatingActionButtonPrivate::FloatingActionButtonPrivate(FloatingActionButton *q)
    : RaisedButtonPrivate(q),
      mini(false),
      corner(Qt::BottomRightCorner)
{
}

FloatingActionButtonPrivate::~FloatingActionButtonPrivate()
{
}

void FloatingActionButtonPrivate::init()
{
    Q_Q(FloatingActionButton);

    q->setRole(Material::Primary);
    q->setFixedSize(56, 56);
    q->setGeometry(fabGeometry());

    assignAnimationProperties();
}

QRect FloatingActionButtonPrivate::fabGeometry() const
{
    Q_Q(const FloatingActionButton);

    QWidget *parent = q->parentWidget();
    if (!parent)
        return QRect();

    const int offset = mini ? 74 : 90;
    const int s = mini ? 40 : 56;

    switch (corner)
    {
    case Qt::TopLeftCorner:
        return QRect(offset - s,
                     offset - s,
                     s, s);
    case Qt::TopRightCorner:
        return QRect(parent->width() - offset,
                     offset - s,
                     s, s);
    case Qt::BottomLeftCorner:
        return QRect(offset -s,
                     parent->height() - offset,
                     s, s);
    case Qt::BottomRightCorner:
    default:
        return QRect(parent->width() - offset,
                     parent->height() - offset,
                     s, s);
    }
}

void FloatingActionButtonPrivate::assignAnimationProperties()
{
    if (mini)
    {
        effect->setColor(QColor(0, 0, 0, 80));

        normalState->assignProperty(effect, "offset", QPointF(0, 3));
        normalState->assignProperty(effect, "blurRadius", 13);
        pressedState->assignProperty(effect, "offset", QPointF(0, 7));
        pressedState->assignProperty(effect, "blurRadius", 20);
    }
    else
    {
        effect->setColor(QColor(0, 0, 0, 110));

        normalState->assignProperty(effect, "offset", QPointF(0, 6));
        normalState->assignProperty(effect, "blurRadius", 16);
        pressedState->assignProperty(effect, "offset", QPointF(0, 11));
        pressedState->assignProperty(effect, "blurRadius", 28);
    }
}

FloatingActionButton::FloatingActionButton(const QIcon &icon, QWidget *parent)
    : RaisedButton(*new FloatingActionButtonPrivate(this), parent)
{
    d_func()->init();

    setIcon(icon);
}

FloatingActionButton::~FloatingActionButton()
{
}

QSize FloatingActionButton::sizeHint() const
{
    Q_D(const FloatingActionButton);

    if (d->mini) {
        return QSize(40, 40);
    }
    return QSize(56, 56);
}

void FloatingActionButton::setMini(bool state)
{
    Q_D(FloatingActionButton);

    if (d->mini == state)
        return;

    d->mini = state;

    if (state) {
        setFixedSize(40, 40);
    } else {
        setFixedSize(56, 56);
    }
    d->assignAnimationProperties();
    update();
}

bool FloatingActionButton::isMini() const
{
    Q_D(const FloatingActionButton);

    return d->mini;
}

void FloatingActionButton::setCorner(Qt::Corner corner)
{
    Q_D(FloatingActionButton);

    if (d->corner == corner)
        return;

    d->corner = corner;
    update();
}

Qt::Corner FloatingActionButton::corner() const
{
    Q_D(const FloatingActionButton);

    return d->corner;
}

bool FloatingActionButton::event(QEvent *event)
{
    QEvent::Type type = event->type();

    if (QEvent::ParentChange == type && parentWidget())
    {
        Q_D(FloatingActionButton);

        parent()->installEventFilter(this);
        setGeometry(d->fabGeometry());
    }
    else if (QEvent::ParentAboutToChange == type && parentWidget())
    {
        parent()->removeEventFilter(this);
    }
    return RaisedButton::event(event);
}

bool FloatingActionButton::eventFilter(QObject *obj, QEvent *event)
{
    QEvent::Type type = event->type();

    if (QEvent::Move == type || QEvent::Resize == type)
    {
        Q_D(FloatingActionButton);

        setGeometry(d->fabGeometry());
    }
    return RaisedButton::eventFilter(obj, event);
}

void FloatingActionButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(FloatingActionButton);

    int s = d->mini ? 40 : 56;

    QRect square = QRect(0, 0, s, s);
    square.moveCenter(rect().center());

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(isEnabled()
       ? backgroundColor() : palette().color(QPalette::Disabled, QPalette::Background));
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    painter.drawEllipse(square);

    const int sz = d->mini ? 18 : 24;

    QRect iconRect(0, 0, sz, sz);
    iconRect.moveCenter(square.center());

    icon().paint(&painter, iconRect, Qt::AlignCenter, QIcon::Normal);
}
