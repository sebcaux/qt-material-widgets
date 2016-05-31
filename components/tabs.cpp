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
    tab->setBgMode(Qt::OpaqueMode);
    tab->setPrimaryTextColor(Qt::white);
    tab->setPeakOpacity(0.25);

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
