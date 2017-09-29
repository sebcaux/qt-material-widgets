#include "tabs.h"
#include "tabs_p.h"
#include <QHBoxLayout>
#include <QPainter>
#include "tabs_internal.h"
#include "lib/ripple.h"
#include "lib/style.h"

TabsPrivate::TabsPrivate(Tabs *q)
    : q_ptr(q),
      inkBar(new TabsInkBar(q)),
      tabLayout(new QHBoxLayout),
      tab(-1),
      useThemeColors(true),
      showHalo(true),
      rippleStyle(Material::CenteredRipple)
{
}

void TabsPrivate::init()
{
    Q_Q(Tabs);

    q->setLayout(tabLayout);
    q->setStyle(&Style::instance());

    tabLayout->setSpacing(0);
    tabLayout->setMargin(0);
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

void Tabs::setUseThemeColors(bool value)
{
    Q_D(Tabs);

    d->useThemeColors = value;
}

bool Tabs::useThemeColors() const
{
    Q_D(const Tabs);

    return d->useThemeColors;
}

void Tabs::setShowHalo(bool state)
{
    Q_D(Tabs);

    d->showHalo = state;

    Tab *tab;
    for (int i = 0; i < d->tabLayout->count(); ++i) {
        QLayoutItem *item = d->tabLayout->itemAt(i);
        if ((tab = static_cast<Tab *>(item->widget()))) {
            tab->setShowHalo(state);
        }
    }
}

bool Tabs::showHalo() const
{
    Q_D(const Tabs);

    return d->showHalo;
}

void Tabs::setRippleStyle(Material::RippleStyle style)
{
    Q_D(Tabs);

    d->rippleStyle = style;

    Tab *tab;
    for (int i = 0; i < d->tabLayout->count(); ++i) {
        QLayoutItem *item = d->tabLayout->itemAt(i);
        if ((tab = static_cast<Tab *>(item->widget()))) {
            tab->setRippleStyle(style);
        }
    }
}

Material::RippleStyle Tabs::rippleStyle() const
{
    Q_D(const Tabs);

    return d->rippleStyle;
}

void Tabs::setInkColor(const QColor &color)
{
    Q_D(Tabs);

    d->inkColor = color;
    setUseThemeColors(false);
}

QColor Tabs::inkColor() const
{
    Q_D(const Tabs);

    if (d->useThemeColors || !d->inkColor.isValid()) {
        return Style::instance().themeColor("accent1");
    } else {
        return d->inkColor;
    }
}

void Tabs::setBackgroundColor(const QColor &color)
{
    Q_D(Tabs);

    d->backgroundColor = color;
    setUseThemeColors(false);

    Tab *tab;
    for (int i = 0; i < d->tabLayout->count(); ++i) {
        QLayoutItem *item = d->tabLayout->itemAt(i);
        if ((tab = static_cast<Tab *>(item->widget()))) {
            tab->setBackgroundColor(color);
        }
    }
}

QColor Tabs::backgroundColor() const
{
    Q_D(const Tabs);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->backgroundColor;
    }
}

void Tabs::setTextColor(const QColor &color)
{
    Q_D(Tabs);

    d->textColor = color;
    setUseThemeColors(false);

    Tab *tab;
    for (int i = 0; i < d->tabLayout->count(); ++i) {
        QLayoutItem *item = d->tabLayout->itemAt(i);
        if ((tab = static_cast<Tab *>(item->widget()))) {
            tab->setTextColor(color);
        }
    }
}

QColor Tabs::textColor() const
{
    Q_D(const Tabs);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return Style::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void Tabs::addTab(const QString &text)
{
    createTab(text);
}

void Tabs::addTab(const QString &text, const QIcon &icon)
{
    Tab *tab = createTab(text);
    tab->setIcon(icon);
    tab->setIconSize(QSize(22, 22));
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

void Tabs::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event)

    Q_D(Tabs);

    d->inkBar->refreshGeometry();
}

void Tabs::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    Q_D(Tabs);

    d->inkBar->refreshGeometry();
}

void Tabs::switchTab()
{
    Q_D(Tabs);

    Tab *oldTab = static_cast<Tab *>(d->tabLayout->itemAt(d->tab)->widget());
    if (oldTab) {
        oldTab->setActive(false);
    }

    Tab *tab = static_cast<Tab *>(sender());
    if (tab) {
        tab->setActive(true);
        d->tab = d->tabLayout->indexOf(tab);
        d->inkBar->animate();
        emit currentChanged(d->tab);
    }
}

Tab *Tabs::createTab(const QString &text)
{
    Q_D(Tabs);

    Tab *tab = new Tab(text);
    tab->setCornerRadius(0);
    tab->setRole(Material::Primary);
    tab->setBackgroundMode(Qt::OpaqueMode);
    tab->setPeakOpacity(0.25);
    tab->setShowHalo(d->showHalo);
    tab->setRippleStyle(d->rippleStyle);

    d->tabLayout->addWidget(tab);

    if (-1 == d->tab) {
        d->tab = 0;
        d->inkBar->refreshGeometry();
        tab->setActive(true);
    }

    connect(tab, SIGNAL(clicked()), this, SLOT(switchTab()));

    return tab;
}
