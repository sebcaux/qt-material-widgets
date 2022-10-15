#include "lib/qtmaterialstyle.h"

#include "lib/qtmaterialtheme.h"

#include <QApplication>
#include <QFontDatabase>
#include <QWidget>

/*!
 *  \class QtMaterialStylePrivate
 *  \internal
 */

QtMaterialStylePrivate::QtMaterialStylePrivate(QtMaterialStyle *q)
    : q_ptr(q),
      theme(nullptr)
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

    if (theme == nullptr)
    {
        return;
    }

    QtMaterialTheme *oldTheme = d->theme;

    d->theme = theme;
    theme->setParent(this);

    applyThemeModifications();

    if (oldTheme != nullptr)
    {
        oldTheme->deleteLater();
    }
}

void QtMaterialStyle::applyThemeModifications()
{
    QWidgetList allWidgets = QApplication::allWidgets();
    for (QWidget *w : allWidgets)
    {
        if (w->windowType() != Qt::Desktop && !w->testAttribute(Qt::WA_SetStyle))
        {
            QEvent e(QEvent::StyleChange);
            QCoreApplication::sendEvent(w, &e);
            w->update();
        }
    }
    emit themeChanged();
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
