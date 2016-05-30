#include "tabs.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QPropertyAnimation>
#include "tabs_p.h"
#include "tabs_internal.h"
#include "lib/ripple.h"
#include "lib/style.h"

TabsPrivate::TabsPrivate(Tabs *q)
    : q_ptr(q),
      tab(-1)
{
}

void TabsPrivate::init()
{
    Q_Q(Tabs);

    delegate = new TabsDelegate(q);

    tabLayout = new QHBoxLayout;
    q->setLayout(tabLayout);
    tabLayout->setSpacing(0);
    tabLayout->setMargin(0);
    tabLayout->setContentsMargins(0, 0, 0, 2);
}

Tabs::Tabs(QWidget *parent)
    : QWidget(parent),
      d_ptr(new TabsPrivate(this))
{
    d_func()->init();
}

Tabs::~Tabs()
{
}

void Tabs::addTab(const QString &text)
{
    Q_D(Tabs);

    Tab *tab = new Tab(text);
    tab->setCornerRadius(0);
    tab->setRippleStyle(Material::CenteredRipple);
    tab->setRole(Material::Primary);
    d->tabLayout->addWidget(tab);

    if (-1 == d->tab) {
        d->tab = 0;
        d->delegate->updateInkBar();
    }

    connect(tab, SIGNAL(clicked()), this, SLOT(switchTab()));
}

void Tabs::setRippleStyle(Material::RippleStyle style)
{
    Q_D(Tabs);

    Tab *tab;
    for (int i = 0; i < d->tabLayout->count(); ++i) {
        QLayoutItem *item = d->tabLayout->itemAt(i);
        if ((tab = static_cast<Tab *>(item->widget()))) {
            tab->setRippleStyle(style);
        }
    }

}

const QLayout *Tabs::tabLayout() const
{
    Q_D(const Tabs);

    return d->tabLayout;
}

int Tabs::currentIndex() const
{
    Q_D(const Tabs);

    return d->tab;
}

void Tabs::paintEvent(QPaintEvent *event)
{
    Q_D(Tabs);

    QPainter painter(this);
    painter.fillRect(d->delegate->inkBarGeometry(),
        Style::instance().themeColor("accent1"));

    QWidget::paintEvent(event);
}

void Tabs::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event)

    Q_D(Tabs);

    d->delegate->updateInkBar();
}

void Tabs::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    Q_D(Tabs);

    d->delegate->updateInkBar();
}

void Tabs::switchTab()
{
    Q_D(Tabs);

    Tab *tab = static_cast<Tab *>(sender());
    if (tab) {
        d->tab = d->tabLayout->indexOf(tab);
        d->delegate->setInkBarGeometry(d->tabLayout->itemAt(d->tab)->geometry());
        emit currentChanged(d->tab);
    }
}

//#include <QHBoxLayout>
//#include <QPainter>
//#include <QPropertyAnimation>
//#include "tabs.h"
//#include "tab.h"
//
//Tabs::Tabs(QWidget *parent)
//    : QWidget(parent),
//      _tabLayout(new QHBoxLayout),
//      _animation(new QPropertyAnimation(this)),
//      _tab(0),
//      _tween(1)
//{
//    _animation->setPropertyName("tween");
//    _animation->setEasingCurve(QEasingCurve::OutCirc);
//    _animation->setTargetObject(this);
//    _animation->setDuration(700);
//
//    setLayout(_tabLayout);
//    _tabLayout->setSpacing(0);
//    _tabLayout->setMargin(0);
//}
//
//Tabs::~Tabs()
//{
//}
//
//void Tabs::addTab(Tab *tab)
//{
//    _tabLayout->addWidget(tab);
//    connect(tab, SIGNAL(clicked()), this, SLOT(switchActiveTab()));
//}
//
//void Tabs::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event)
//
//    QPainter painter(this);
//    painter.fillRect(_inkBarGeometry, Qt::black);
//}
//
//void Tabs::switchActiveTab()
//{
//    Tab *tab = static_cast<Tab *>(sender());
//    if (tab) {
//        _previousGeometry = _inkBarGeometry;
//        _tab = _tabLayout->indexOf(tab);
//        _inkBarGeometry = _tabLayout->itemAt(_tab)->geometry();
//        _animation->stop();
//        _animation->setStartValue(0);
//        _animation->setEndValue(1);
//        _animation->start();
//        emit currentChanged(_tab);
//    }
//}
//
//void Tabs::moveEvent(QMoveEvent *event)
//{
//    Q_UNUSED(event)
//
//    UpdateInkBar();
//}
//
//void Tabs::resizeEvent(QResizeEvent *event)
//{
//    Q_UNUSED(event)
//
//    updateInkBar();
//}
//
//void Tabs::updateInkBar()
//{
//    QLayoutItem *item = _tabLayout->itemAt(_tab);
//    if (item) {
//        const QRect &r = item->geometry();
//        const qreal s = 1-_tween;
//        if (QAbstractAnimation::Running != _animation->state()) {
//            _inkBarGeometry = QRect(r.left(), r.bottom()-1, r.width(), 2);
//        } else {
//            const qreal left = _previousGeometry.left()*s + r.left()*_tween;
//            const qreal width = _previousGeometry.width()*s + r.width()*_tween;
//            _inkBarGeometry = QRect(left, r.bottom()-1, width, 2);
//        }
//        update();
//    }
//}
//
