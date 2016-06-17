#ifndef BADGE_P_H
#define BADGE_P_H

#include <QObject>

class Badge;

class BadgePrivate
{
    Q_DISABLE_COPY(BadgePrivate)
    Q_DECLARE_PUBLIC(Badge)

public:
    BadgePrivate(Badge *q);
    ~BadgePrivate();

    void init();

    Badge *const q_ptr;
    QSize        size;
    int          padding;
    QString      text;
    QIcon        icon;
    bool         useThemeColors;
    QColor       textColor;
    QColor       backgroundColor;
};

#endif // BADGE_P_H
