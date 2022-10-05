#ifndef QTMATERIALSTYLE_H
#define QTMATERIALSTYLE_H

#include <QCommonStyle>

#include "lib/qtmaterialstyle_p.h"
#include "lib/qtmaterialtheme.h"

class QtMaterialStyle : public QCommonStyle
{
    Q_OBJECT

public:
    inline static QtMaterialStyle &instance();

    QtMaterialTheme *theme() const;
    void setTheme(QtMaterialTheme *theme);
    void applyThemeModifications() const;

    const QColor &themeColor(Material::ThemeColor colorTheme) const;
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
