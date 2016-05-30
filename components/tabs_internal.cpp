#include "tabs_internal.h"
#include <QLayout>
#include <QPropertyAnimation>
#include "tabs.h"

TabsDelegate::TabsDelegate(Tabs *parent)
    : QObject(parent),
      tabs(parent),
      _animation(new QPropertyAnimation(parent)),
      _tween(0)
{
    _animation->setPropertyName("tween");
    _animation->setEasingCurve(QEasingCurve::OutCirc);
    _animation->setTargetObject(this);
    _animation->setDuration(700);
}

TabsDelegate::~TabsDelegate()
{
}

void TabsDelegate::setTween(qreal tween)
{
    _tween = tween;
    updateInkBar();
}

void TabsDelegate::setInkBarGeometry(const QRect &newGeometry)
{
    _previousGeometry = _inkBarGeometry;
    _inkBarGeometry = newGeometry;

    _animation->stop();
    _animation->setStartValue(0);
    _animation->setEndValue(1);
    _animation->start();
}

void TabsDelegate::updateInkBar()
{
    QLayoutItem *item = tabs->tabLayout()->itemAt(tabs->currentIndex());
    if (item) {
        const QRect &r = item->geometry();
        const qreal s = 1-_tween;
        if (QAbstractAnimation::Running != _animation->state()) {
            _inkBarGeometry = QRect(r.left(), r.bottom()+1, r.width(), 2);
        } else {
            const qreal left = _previousGeometry.left()*s + r.left()*_tween;
            const qreal width = _previousGeometry.width()*s + r.width()*_tween;
            _inkBarGeometry = QRect(left, r.bottom()+1, width, 2);
        }
        tabs->update();
    }
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
