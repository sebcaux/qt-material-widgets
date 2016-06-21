#include "fab.h"
#include "fab_p.h"
#include <QPainter>
#include <QGraphicsDropShadowEffect>

FloatingActionButtonPrivate::FloatingActionButtonPrivate(FloatingActionButton *q)
    : RaisedButtonPrivate(q),
      mini(false),
      offsX(34),
      offsY(36),
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

    QPainterPath path;
    path.addEllipse(0, 0, 56, 56);
    ripple->setClipPath(path);
    ripple->setClipping(true);

    if (q->parentWidget()) {
        q->parentWidget()->installEventFilter(q);
    }

    q->setFixedRippleRadius(50);
}

QRect FloatingActionButtonPrivate::fabGeometry() const
{
    Q_Q(const FloatingActionButton);

    QWidget *parent = q->parentWidget();
    if (!parent)
        return QRect();

    const int s = mini ? 40 : 56;

    switch (corner)
    {
    case Qt::TopLeftCorner:
        return QRect(offsX,
                     offsY,
                     s, s);
    case Qt::TopRightCorner:
        return QRect(parent->width() - (offsX + s),
                     offsY,
                     s, s);
    case Qt::BottomLeftCorner:
        return QRect(offsX,
                     parent->height() - (offsY + s),
                     s, s);
    case Qt::BottomRightCorner:
    default:
        return QRect(parent->width() - (offsX + s),
                     parent->height() - (offsY + s),
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

    const int s = state ? 40 : 56;

    setFixedSize(s, s);
    QPainterPath path;
    path.addEllipse(0, 0, s, s);
    d->ripple->setClipPath(path);

    setFixedRippleRadius(state ? 30 : 50);

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

void FloatingActionButton::setOffset(int x, int y)
{
    Q_D(FloatingActionButton);

    d->offsX = x;
    d->offsY = y;
    update();
}

QSize FloatingActionButton::offset() const
{
    Q_D(const FloatingActionButton);

    return QSize(d->offsX, d->offsY);
}

void FloatingActionButton::setXOffset(int x)
{
    Q_D(FloatingActionButton);

    d->offsX = x;
    update();
}

int FloatingActionButton::xOffset() const
{
    Q_D(const FloatingActionButton);

    return d->offsX;
}

void FloatingActionButton::setYOffset(int y)
{
    Q_D(FloatingActionButton);

    d->offsY = y;
    update();
}

int FloatingActionButton::yOffset() const
{
    Q_D(const FloatingActionButton);

    return d->offsY;
}

bool FloatingActionButton::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::ParentChange:
    {
        if (!parent())
            break;

        Q_D(FloatingActionButton);

        parent()->installEventFilter(this);
        setGeometry(d->fabGeometry());
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
       ? backgroundColor()
       : disabledTextColor());
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    painter.drawEllipse(square);

    const int sz = d->mini ? 18 : 24;

    QRect iconRect(0, 0, sz, sz);
    iconRect.moveCenter(square.center());

    icon().paint(&painter, iconRect, Qt::AlignCenter, QIcon::Normal);
}
