#ifndef THEME_P_H
#define THEME_P_H

#include "theme.h"

class ThemePrivate
{
    Q_DISABLE_COPY(ThemePrivate)
    Q_DECLARE_PUBLIC(Theme)

public:
    ThemePrivate(Theme *q)
        : q_ptr(q)
    {}

    QColor rgba(int r, int g, int b, qreal a) const;

    Theme *const q_ptr;

    QHash<QString, QColor> colors;
};

#endif // THEME_P_H
