#include "lib/qtmaterialstyle.h"

#include "lib/qtmaterialtheme.h"

#include <QFontDatabase>

/*!
 *  \class QtMaterialStylePrivate
 *  \internal
 */

QtMaterialStylePrivate::QtMaterialStylePrivate(QtMaterialStyle *q)
    : q_ptr(q)
{
}

QtMaterialStylePrivate::~QtMaterialStylePrivate()
{
}

void QtMaterialStylePrivate::init()
{
    Q_Q(QtMaterialStyle);

    QFontDatabase::addApplicationFont(":/fonts/roboto_regular");
    QFontDatabase::addApplicationFont(":/fonts/roboto_medium");
    QFontDatabase::addApplicationFont(":/fonts/roboto_bold");

    q->setTheme(new QtMaterialTheme);
}

/*!
 *  \class QtMaterialStyle
 *  \internal
 */

QtMaterialTheme *QtMaterialStyle::theme() const
{
    Q_D(const QtMaterialStyle);

    return d->theme;
}

void QtMaterialStyle::setTheme(QtMaterialTheme *theme)
{
    Q_D(QtMaterialStyle);

    d->theme = theme;
    theme->setParent(this);
}

const QColor &QtMaterialStyle::themeColor(Material::ThemeColor themeColor) const
{
    Q_D(const QtMaterialStyle);

    Q_ASSERT(d->theme);

    return d->theme->color(themeColor);
}

const QFont &QtMaterialStyle::themeFont(Material::FontType fontType) const
{
    Q_D(const QtMaterialStyle);

    Q_ASSERT(d->theme);

    return d->theme->font(fontType);
}

QtMaterialStyle::QtMaterialStyle()
    : d_ptr(new QtMaterialStylePrivate(this))
{
    d_func()->init();
}
