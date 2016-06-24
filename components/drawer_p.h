#ifndef DRAWER_P_H
#define DRAWER_P_H

#include <QObject>

class Drawer;
class DrawerStateMachine;

class DrawerPrivate
{
    Q_DISABLE_COPY(DrawerPrivate)
    Q_DECLARE_PUBLIC(Drawer)

public:
    DrawerPrivate(Drawer *q);

    Drawer             *const q_ptr;
    DrawerStateMachine *const stateMachine;
    QWidget            *const window;
    int                       width;
};

#endif // DRAWER_P_H
