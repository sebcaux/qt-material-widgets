#ifndef ICONBUTTON_P_H
#define ICONBUTTON_P_H

class IconButton;
class RippleOverlay;

class IconButtonPrivate
{
    Q_DISABLE_COPY(IconButtonPrivate)
    Q_DECLARE_PUBLIC(IconButton)

public:
    IconButtonPrivate(IconButton *q);

    void init();

    IconButton *const q_ptr;
    RippleOverlay *ripple;
};

#endif // ICONBUTTON_P_H
