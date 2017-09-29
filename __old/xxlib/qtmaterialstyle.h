#ifndef QTMATERIALSTYLE_H
#define QTMATERIALSTYLE_H

#include <QCommonStyle>
#include "xxlib/qtmaterialstyle_p.h"

class QtMaterialTheme;

class QtMaterialStyle : public QCommonStyle
{
    Q_OBJECT

public:
    inline static QtMaterialStyle &instance();

    void setTheme(QtMaterialTheme *theme);
    QColor themeColor(const QString &key) const;

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

#endif // QTMATERIALSTYLE_H
