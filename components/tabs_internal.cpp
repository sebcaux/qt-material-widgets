#include "tabs_internal.h"
#include <QLayout>
#include <QPainter>
#include <QEvent>
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
    QEvent::Type type = event->type();

    if (QEvent::ParentChange == type) {
        setParent(tabs->parentWidget());
    } else if (QEvent::Resize == type || QEvent::Move == type) {
        QWidget *widget;
        if ((widget = parentWidget())) {
            setGeometry(widget->rect());
        }
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
    : FlatButton(parent)
{
    init();
}

Tab::Tab(QString text, QWidget *parent)
    : FlatButton(parent)
{
    init();

    setText(text);
}

Tab::~Tab()
{
}

void Tab::init()
{
    setMinimumHeight(50);
}
