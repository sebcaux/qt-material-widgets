#ifndef QTMATERIALSTYLE_H
#define QTMATERIALSTYLE_H

#include "../qtmaterialwidgets.h"

#include <QCommonStyle>

#include "lib/qtmaterialstyle_p.h"
#include "lib/qtmaterialtheme.h"

class QTMATERIALWIDGETS_EXPORT QtMaterialStyle : public QCommonStyle
{
    Q_OBJECT

public:
    static QtMaterialStyle &instance();

    QtMaterialTheme *theme() const;
    void setTheme(QtMaterialTheme *theme);
    void applyThemeModifications();

    const QColor &themeColor(Material::ThemeColor colorTheme) const;
    const QFont &themeFont(Material::FontType fontType) const;

signals:
    void themeChanged();

protected:
    const QScopedPointer<QtMaterialStylePrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialStyle)
    Q_DECLARE_PRIVATE(QtMaterialStyle)

    QtMaterialStyle();
};

#endif  // QTMATERIALSTYLE_H
