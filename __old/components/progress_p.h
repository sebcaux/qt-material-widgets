#ifndef PROGRESS_P_H
#define PROGRESS_P_H

#include <QObject>
#include "lib/theme.h"

class Progress;
class ProgressDelegate;

class ProgressPrivate
{
    Q_DISABLE_COPY(ProgressPrivate)
    Q_DECLARE_PUBLIC(Progress)

public:
    ProgressPrivate(Progress *q);
    ~ProgressPrivate();

    void init();

    Progress         *const q_ptr;
    ProgressDelegate *const delegate;
    Material::ProgressType  progressType;
    QColor                  progressColor;
    QColor                  backgroundColor;
    bool                    useThemeColors;
};

#endif // PROGRESS_P_H
