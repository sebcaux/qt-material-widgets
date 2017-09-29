#ifndef AVATAR_P_H
#define AVATAR_P_H

#include <QObject>
#include <QImage>
#include <QIcon>
#include <QPixmap>
#include "lib/theme.h"

class Avatar;

class AvatarPrivate
{
    Q_DISABLE_COPY(AvatarPrivate)
    Q_DECLARE_PUBLIC(Avatar)

public:
    AvatarPrivate(Avatar *q);

    void init();

    Avatar        *const q_ptr;
    int                  size;
    Material::AvatarType type;
    QChar                letter;
    QImage               image;
    QIcon                icon;
    QPixmap              pixmap;
    bool                 useThemeColors;
    QColor               textColor;
    QColor               backgroundColor;
};

#endif // AVATAR_P_H
