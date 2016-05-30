#ifndef TABS_P_H
#define TABS_P_H

#include <QRect>

class QHBoxLayout;
class Tabs;
class TabsDelegate;

class TabsPrivate
{
    Q_DISABLE_COPY(TabsPrivate)
    Q_DECLARE_PUBLIC(Tabs)

public:
    TabsPrivate(Tabs *q);

    void init();

    Tabs *const q_ptr;
    TabsDelegate *delegate;
    QHBoxLayout  *tabLayout;
    int tab;
};

#endif // TABS_P_H
