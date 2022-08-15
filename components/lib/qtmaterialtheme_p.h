#ifndef QTMATERIALTHEME_P_H
#define QTMATERIALTHEME_P_H

#include <QColor>
#include <QFont>
#include <QHash>

class QtMaterialTheme;

class QtMaterialThemePrivate
{
    Q_DISABLE_COPY(QtMaterialThemePrivate)
    Q_DECLARE_PUBLIC(QtMaterialTheme)

public:
    QtMaterialThemePrivate(QtMaterialTheme *q);
    ~QtMaterialThemePrivate();

    QColor rgba(int r, int g, int b, qreal a) const;

    QtMaterialTheme *const q_ptr;
    QHash<QString, QColor> colors;
    QVector<QFont> fonts;  // QVector to garentee same funtionnalities on Qt5 as Qt6
};

#endif  // QTMATERIALTHEME_P_H
