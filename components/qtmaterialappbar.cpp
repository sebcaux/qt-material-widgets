#include "qtmaterialappbar.h"

#include "lib/qtmaterialstyle.h"
#include "qtmaterialappbar_internal.h"
#include "qtmaterialappbar_p.h"

#include <QGraphicsDropShadowEffect>
#include <QPainter>

/*!
 *  \class QtMaterialAppBarPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialAppBarPrivate::QtMaterialAppBarPrivate(QtMaterialAppBar *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialAppBarPrivate::~QtMaterialAppBarPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialAppBarPrivate::init()
{
    Q_Q(QtMaterialAppBar);

    navIconType = Material::NavIconNone;
    navButton = nullptr;

    titleLabel = new QLabel(q);
    titleLabel->setAttribute(Qt::WA_TranslucentBackground);
    titleLabel->setForegroundRole(QPalette::WindowText);
    titleLabel->setContentsMargins(6, 0, 0, 0);
    QPalette palette = titleLabel->palette();
    palette.setColor(titleLabel->foregroundRole(), Qt::white);
    titleLabel->setPalette(palette);
    titleLabel->setFont(QtMaterialStyle::instance().themeFont(Material::FontHeadline3));

    useThemeColors = true;

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(11);
    effect->setColor(QColor(0, 0, 0, 50));
    effect->setOffset(0, 3);
    q->setGraphicsEffect(effect);

    layout = new QtMaterialAppBarLayout(q);
    layout->setTitleLabel(titleLabel);
    q->setLayout(layout);
}

/*!
 *  \internal
 */
void QtMaterialAppBarPrivate::setNavIconType(Material::NavIconType type)
{
    Q_Q(QtMaterialAppBar);

    if (navButton == nullptr && type != Material::NavIconNone)
    {
        navButton = new QtMaterialIconButton(QIcon(), q);
        navButton->setIconSize(QSize(48, 48));
        navButton->setColor(QtMaterialStyle::instance().themeColor("alternateText"));
        navButton->setFixedWidth(64);
        layout->setNavButton(navButton);
    }

    switch (type)
    {
        case Material::NavIconNone:
            if (navButton != nullptr)
            {
                layout->setNavButton(nullptr);
                navButton = nullptr;
                delete navButton;
            }
            break;

        case Material::NavIconMenu:
            navButton->setIcon(QtMaterialTheme::icon("navigation", "menu"));
            break;

        case Material::NavIconPrevious:
            navButton->setIcon(QtMaterialTheme::icon("navigation", "arrow_back"));
            break;

        case Material::NavIconUpper:
            navButton->setIcon(QtMaterialTheme::icon("navigation", "expand_less"));
            break;
    }
    navIconType = type;
}

/*!
 *  \class QtMaterialAppBar
 */

QtMaterialAppBar::QtMaterialAppBar(const QString &title, QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialAppBarPrivate(this))
{
    d_func()->init();

    setTitle(title);
}

QtMaterialAppBar::QtMaterialAppBar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialAppBarPrivate(this))
{
    d_func()->init();
}

QtMaterialAppBar::~QtMaterialAppBar()
{
}

const QString &QtMaterialAppBar::title() const
{
    Q_D(const QtMaterialAppBar);

    return d->title;
}

void QtMaterialAppBar::setTitle(const QString &title)
{
    Q_D(QtMaterialAppBar);

    d->title = title;
    if (d->titleLabel != nullptr)
    {
        d->titleLabel->setText(title);
    }
}

Material::NavIconType QtMaterialAppBar::navIconType() const
{
    Q_D(const QtMaterialAppBar);

    return d->navIconType;
}

void QtMaterialAppBar::setNavIconType(Material::NavIconType navIconType)
{
    Q_D(QtMaterialAppBar);

    d->setNavIconType(navIconType);
}

void QtMaterialAppBar::setUseThemeColors(bool value)
{
    Q_D(QtMaterialAppBar);

    if (d->useThemeColors == value)
    {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialAppBar::useThemeColors() const
{
    Q_D(const QtMaterialAppBar);

    return d->useThemeColors;
}

void QtMaterialAppBar::setForegroundColor(const QColor &color)
{
    Q_D(QtMaterialAppBar);

    d->foregroundColor = color;

    if (d->useThemeColors)
    {
        d->useThemeColors = false;
    }
    update();
}

QColor QtMaterialAppBar::foregroundColor() const
{
    Q_D(const QtMaterialAppBar);

    if (d->useThemeColors || !d->foregroundColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor("primary1");
    }

    return d->foregroundColor;
}

void QtMaterialAppBar::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialAppBar);

    d->backgroundColor = color;

    if (d->useThemeColors)
    {
        d->useThemeColors = false;
    }
    update();
}

QColor QtMaterialAppBar::backgroundColor() const
{
    Q_D(const QtMaterialAppBar);

    if (d->useThemeColors || !d->backgroundColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor("primary1");
    }

    return d->backgroundColor;
}

QSize QtMaterialAppBar::sizeHint() const
{
    return QSize(-1, 64);
}

void QtMaterialAppBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.fillRect(rect(), backgroundColor());
}
