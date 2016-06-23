#include "drawer.h"
#include "drawer_p.h"

DrawerPrivate(Drawer *q)
    : q_ptr(q)
{
}

Drawer::Drawer(QWidget *parent)
    : QWidget(parent)
{
}

Drawer::~Drawer()
{
}
