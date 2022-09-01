#ifndef QTMATERIALSTYLE_H
#define QTMATERIALSTYLE_H

#include <QCommonStyle>

#include "lib/qtmaterialstyle_p.h"
#include "lib/qtmaterialtheme.h"

#define MATERIAL_DISABLE_THEME_COLORS                                                                                                                                              \
    if (d->useThemeColors == true)                                                                                                                                                 \
    {                                                                                                                                                                              \
        d->useThemeColors = false;                                                                                                                                                 \
    }

class QtMaterialStyle : public QCommonStyle
{
    Q_OBJECT

public:
    inline static QtMaterialStyle &instance();

    void setTheme(QtMaterialTheme *theme);

    QColor themeColor(Material::ThemeColor colorTheme) const;
    const QFont &themeFont(Material::FontType fontType) const;

protected:
    const QScopedPointer<QtMaterialStylePrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(QtMaterialStyle)

    QtMaterialStyle();

    QtMaterialStyle(QtMaterialStyle const &);
    void operator=(QtMaterialStyle const &);
};

inline QtMaterialStyle &QtMaterialStyle::instance()
{
    static QtMaterialStyle instance;
    return instance;
}

#endif  // QTMATERIALSTYLE_H
