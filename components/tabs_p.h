#ifndef TABS_P_H
#define TABS_P_H

#include <QRect>
#include <QColor>

class QHBoxLayout;
class Tabs;
class TabsInkBar;

class TabsPrivate
{
    Q_DISABLE_COPY(TabsPrivate)
    Q_DECLARE_PUBLIC(Tabs)

public:
    TabsPrivate(Tabs *q);

    void init();

    Tabs        *const q_ptr;
    TabsInkBar  *inkBar;
    QHBoxLayout *tabLayout;
    QColor       inkColor;
    QColor       backgroundColor;
    QColor       textColor;
    int          tab;
    bool         useThemeColors;
    bool         showHalo;
};

#endif // TABS_P_H
