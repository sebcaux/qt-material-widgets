#ifndef FAB_P_H
#define FAB_P_H

#include "raisedbutton_p.h"

class FloatingActionButtonPrivate : public RaisedButtonPrivate
{
    Q_DISABLE_COPY(FloatingActionButtonPrivate)
    Q_DECLARE_PUBLIC(FloatingActionButton)

public:
    FloatingActionButtonPrivate(FloatingActionButton *q);
    ~FloatingActionButtonPrivate();

    void init();

    QRect fabGeometry() const;

    void assignAnimationProperties();

    bool mini;
    Qt::Corner corner;
};

#endif // FAB_P_H
