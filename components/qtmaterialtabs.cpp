#include "qtmaterialtabs.h"

#include "lib/qtmaterialstyle.h"
#include "qtmaterialtabs_internal.h"
#include "qtmaterialtabs_p.h"

#include <QHBoxLayout>

/*!
 *  \QtMaterialTabsPrivate
 *  \internal
 */

QtMaterialTabsPrivate::QtMaterialTabsPrivate(QtMaterialTabs *q)
    : q_ptr(q)
{
}

QtMaterialTabsPrivate::~QtMaterialTabsPrivate()
{
}

void QtMaterialTabsPrivate::init()
{
    Q_Q(QtMaterialTabs);

    inkBar = new QtMaterialTabsInkBar(q);
    rippleStyle = Material::CenteredRipple;
    tab = -1;
    showHalo = false;
    useThemeColors = true;
    iconSize = QSize(24, 24);

    q->setStyle(&QtMaterialStyle::instance());
    q->setFont(QtMaterialStyle::instance().themeFont(Material::FontButton));

    tabLayout = new QHBoxLayout;
    tabLayout->setSpacing(0);
    tabLayout->setContentsMargins(0, 0, 0, 0);
    q->setLayout(tabLayout);
}

/*!
 *  \QtMaterialTabs
 */

QtMaterialTabs::QtMaterialTabs(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialTabsPrivate(this))
{
    d_func()->init();
}

QtMaterialTabs::~QtMaterialTabs()
{
}

void QtMaterialTabs::setUseThemeColors(bool value)
{
    Q_D(QtMaterialTabs);

    d->useThemeColors = value;
}

bool QtMaterialTabs::useThemeColors() const
{
    Q_D(const QtMaterialTabs);

    return d->useThemeColors;
}

const QSize &QtMaterialTabs::iconSize() const
{
    Q_D(const QtMaterialTabs);

    return d->iconSize;
}

void QtMaterialTabs::setIconSize(const QSize &iconSize)
{
    Q_D(QtMaterialTabs);

    d->iconSize = iconSize;
    updateTabs();
}

void QtMaterialTabs::setIconSize(int w, int h)
{
    setIconSize(QSize(w, h));
}

void QtMaterialTabs::setHaloVisible(bool value)
{
    Q_D(QtMaterialTabs);

    d->showHalo = value;
    updateTabs();
}

bool QtMaterialTabs::isHaloVisible() const
{
    Q_D(const QtMaterialTabs);

    return d->showHalo;
}

void QtMaterialTabs::setRippleStyle(Material::RippleStyle style)
{
    Q_D(QtMaterialTabs);

    d->rippleStyle = style;
    updateTabs();
}

Material::RippleStyle QtMaterialTabs::rippleStyle() const
{
    Q_D(const QtMaterialTabs);

    return d->rippleStyle;
}

void QtMaterialTabs::setInkColor(const QColor &color)
{
    Q_D(QtMaterialTabs);

    d->inkColor = color;

    d->useThemeColors = false;
    d->inkBar->update();
    update();
}

QColor QtMaterialTabs::inkColor() const
{
    Q_D(const QtMaterialTabs);

    if (d->useThemeColors || !d->inkColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeSecondaryMain);
    }

    return d->inkColor;
}

void QtMaterialTabs::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialTabs);

    d->backgroundColor = color;

    d->useThemeColors = false;
    updateTabs();
    update();
}

QColor QtMaterialTabs::backgroundColor() const
{
    Q_D(const QtMaterialTabs);

    if (d->useThemeColors || !d->backgroundColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemePrimaryMain);
    }

    return d->backgroundColor;
}

void QtMaterialTabs::setTextColor(const QColor &color)
{
    Q_D(QtMaterialTabs);

    d->textColor = color;

    d->useThemeColors = false;
    updateTabs();
    update();
}

QColor QtMaterialTabs::textColor() const
{
    Q_D(const QtMaterialTabs);

    if (d->useThemeColors || !d->textColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeCanvas);
    }

    return d->textColor;
}

void QtMaterialTabs::setCurrentIndex(int index)
{
    Q_D(QtMaterialTabs);

    setTabActive(d->tab, false);
    d->tab = index;
    setTabActive(index, true);
    d->inkBar->animate();

    emit currentChanged(index);
}

void QtMaterialTabs::addTab(const QString &text)
{
    addTab(QIcon(), text);
}

void QtMaterialTabs::addTab(const QIcon &icon, const QString &text)
{
    Q_D(QtMaterialTabs);

    QtMaterialTab *tab = new QtMaterialTab(this);
    tab->setText(text);
    tab->setHaloVisible(d->showHalo);
    tab->setRippleStyle(d->rippleStyle);

    if (!icon.isNull())
    {
        tab->setIcon(icon);
        tab->setIconSize(d->iconSize);
    }

    d->tabLayout->addWidget(tab);
    connect(tab,
            &QtMaterialTab::clicked,
            this,
            [=]()
            {
                setCurrentIndex(d->tabLayout->indexOf(tab));
            });

    if (d->tab == -1)
    {
        d->tab = 0;
        d->inkBar->refreshGeometry();
        d->inkBar->raise();
        tab->setActive(true);
    }
}

QString QtMaterialTabs::tabText(int index) const
{
    Q_D(const QtMaterialTabs);

    if (const QtMaterialTab *tab = static_cast<QtMaterialTab *>(d->tabLayout->itemAt(index)->widget()))
    {
        return tab->text();
    }

    return QString();
}

void QtMaterialTabs::setTabText(int index, const QString &text)
{
    Q_D(QtMaterialTabs);

    if (QtMaterialTab *tab = static_cast<QtMaterialTab *>(d->tabLayout->itemAt(index)->widget()))
    {
        tab->setText(text);
    }
}

QIcon QtMaterialTabs::tabIcon(int index) const
{
    Q_D(const QtMaterialTabs);

    if (const QtMaterialTab *tab = static_cast<QtMaterialTab *>(d->tabLayout->itemAt(index)->widget()))
    {
        return tab->icon();
    }

    return QIcon();
}

void QtMaterialTabs::setTabIcon(int index, const QIcon &icon)
{
    Q_D(QtMaterialTabs);

    if (QtMaterialTab *tab = static_cast<QtMaterialTab *>(d->tabLayout->itemAt(index)->widget()))
    {
        tab->setIcon(icon);
    }

    d->inkBar->refreshGeometry();
    d->inkBar->animate();
}

int QtMaterialTabs::currentIndex() const
{
    Q_D(const QtMaterialTabs);

    return d->tab;
}

int QtMaterialTabs::count() const
{
    Q_D(const QtMaterialTabs);

    return d->tabLayout->count();
}

void QtMaterialTabs::setTabActive(int index, bool active)
{
    Q_D(QtMaterialTabs);

    if (index > -1)
    {
        QtMaterialTab *tab = static_cast<QtMaterialTab *>(d->tabLayout->itemAt(index)->widget());
        if (tab != nullptr)
        {
            tab->setActive(active);
        }
    }
}

void QtMaterialTabs::updateTabs()
{
    Q_D(QtMaterialTabs);

    for (int i = 0; i < d->tabLayout->count(); ++i)
    {
        QLayoutItem *item = d->tabLayout->itemAt(i);
        QtMaterialTab *tab = static_cast<QtMaterialTab *>(item->widget());
        if (tab != nullptr)
        {
            tab->setRippleStyle(d->rippleStyle);
            tab->setHaloVisible(d->showHalo);
            tab->setBackgroundColor(backgroundColor());
            tab->setForegroundColor(textColor());
            tab->setIconSize(d->iconSize);
        }
    }
}
