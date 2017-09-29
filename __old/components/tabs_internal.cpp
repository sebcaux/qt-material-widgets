#include "tabs_internal.h"
#include <QLayout>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOptionButton>
#include <QEvent>
#include <QDebug>
#include <QPropertyAnimation>
#include "tabs.h"

TabsInkBar::TabsInkBar(Tabs *parent)
    : QWidget(parent->parentWidget()),
      tabs(parent),
      _animation(new QPropertyAnimation(parent)),
      _tween(0)
{
    parent->installEventFilter(this);

    _animation->setPropertyName("tweenValue");
    _animation->setEasingCurve(QEasingCurve::OutCirc);
    _animation->setTargetObject(this);
    _animation->setDuration(700);
}

TabsInkBar::~TabsInkBar()
{
}

void TabsInkBar::setTweenValue(qreal value)
{
    _tween = value;
    refreshGeometry();
}

void TabsInkBar::refreshGeometry()
{
    QLayoutItem *item = tabs->tabLayout()->itemAt(tabs->currentIndex());
    if (item) {
        const QRect &r = item->geometry();
        const qreal s = 1-_tween;
        if (QAbstractAnimation::Running != _animation->state()) {
            setGeometry(r.left(), r.bottom()-1, r.width(), 2);
        } else {
            const qreal left = _previousGeometry.left()*s + r.left()*_tween;
            const qreal width = _previousGeometry.width()*s + r.width()*_tween;
            setGeometry(left, r.bottom()-1, width, 2);
        }
        tabs->update();
    }
}

void TabsInkBar::animate()
{
    _previousGeometry = geometry();

    _animation->stop();
    _animation->setStartValue(0);
    _animation->setEndValue(1);
    _animation->start();
}

bool TabsInkBar::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::ParentChange:
        setParent(tabs->parentWidget());
        break;
    case QEvent::Resize:
    case QEvent::Move:
        QWidget *widget;
        if ((widget = parentWidget())) {
            setGeometry(widget->rect());
        }
        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}

void TabsInkBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setBrush(tabs->inkColor());
    painter.setOpacity(1);
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());

    QWidget::paintEvent(event);
}

Tab::Tab(QWidget *parent)
    : FlatButton(parent),
      _active(false)
{
    init();
}

Tab::Tab(QString text, QWidget *parent)
    : FlatButton(parent),
      _active(false)
{
    init();

    setText(text);
}

Tab::~Tab()
{
}

QSize Tab::sizeHint() const
{
    if (icon().isNull()) {
        return FlatButton::sizeHint();
    } else {
        return QSize(40, iconSize().height() + 46);
    }
}

void Tab::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(backgroundColor());
    painter.setOpacity(1);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());

    paintHalo(&painter);

    QStylePainter style(this);

    if (!icon().isNull()) {
        style.translate(0, 12);
    }

    QStyleOptionButton option;
    initStyleOption(&option);
    option.features |= QStyleOptionButton::Flat;
    option.iconSize = QSize(-1, -1);  // Prevent icon from being drawn twice

    style.drawControl(QStyle::CE_PushButtonLabel, option);

    if (!icon().isNull()) {
        const QSize &size = iconSize();
        QRect iconRect(QPoint((width()-size.width())/2, 0), size);
        icon().paint(&painter, iconRect, Qt::AlignCenter, QIcon::Normal);
    }

    if (!_active) {
        QColor overlayColor = backgroundColor();
        overlayColor.setAlphaF(0.36);

        QBrush overlay;
        overlay.setStyle(Qt::SolidPattern);
        overlay.setColor(overlayColor);
        painter.fillRect(rect(), overlay);
    }

#ifdef DEBUG_LAYOUT
    QPainter debug(this);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    debug.setPen(pen);
    debug.setBrush(Qt::NoBrush);
    debug.drawRect(rect());
#endif
}

void Tab::init()
{
    setMinimumHeight(50);

    QFont fnt(font());
    fnt.setStyleName("Normal");
    setFont(fnt);
}
