#ifndef AVATAR_P_H
#define AVATAR_P_H

#include <QObject>

class Avatar;

class AvatarPrivate
{
    Q_DISABLE_COPY(AvatarPrivate)
    Q_DECLARE_PUBLIC(Avatar)

public:
    AvatarPrivate(Avatar *q);

    void init();

    Avatar *const q_ptr;
    int size;
};

#endif // AVATAR_P_H
