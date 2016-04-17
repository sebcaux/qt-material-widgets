#include <QHBoxLayout>
#include <QPainter>
#include <QPropertyAnimation>
#include "tabs.h"
#include "tab.h"

Tabs::Tabs(QWidget *parent)
    : QWidget(parent),
      _tabLayout(new QHBoxLayout),
      _animation(new QPropertyAnimation(this)),
      _tab(0),
      _tween(1)
{
    _animation->setPropertyName("tween");
    _animation->setEasingCurve(QEasingCurve::OutCirc);
    _animation->setTargetObject(this);
    _animation->setDuration(700);

    setLayout(_tabLayout);
    _tabLayout->setSpacing(0);
    _tabLayout->setMargin(0);
}

Tabs::~Tabs()
{
}

void Tabs::addTab(Tab *tab)
{
    _tabLayout->addWidget(tab);
    connect(tab, SIGNAL(clicked()), this, SLOT(switchActiveTab()));
}

void Tabs::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.fillRect(_inkBarGeometry, Qt::black);
}

void Tabs::switchActiveTab()
{
    Tab *tab = static_cast<Tab *>(sender());
    if (tab) {
        _previousGeometry = _inkBarGeometry;
        _tab = _tabLayout->indexOf(tab);
        _inkBarGeometry = _tabLayout->itemAt(_tab)->geometry();
        _animation->stop();
        _animation->setStartValue(0);
        _animation->setEndValue(1);
        _animation->start();
        emit currentChanged(_tab);
    }
}

void Tabs::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event)

    updateInkBar();
}

void Tabs::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    updateInkBar();
}

void Tabs::updateInkBar()
{
    QLayoutItem *item = _tabLayout->itemAt(_tab);
    if (item) {
        const QRect &r = item->geometry();
        const qreal s = 1-_tween;
        if (QAbstractAnimation::Running != _animation->state()) {
            _inkBarGeometry = QRect(r.left(), r.bottom()-1, r.width(), 2);
        } else {
            const qreal left = _previousGeometry.left()*s + r.left()*_tween;
            const qreal width = _previousGeometry.width()*s + r.width()*_tween;
            _inkBarGeometry = QRect(left, r.bottom()-1, width, 2);
        }
        update();
    }
}
