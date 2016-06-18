#ifndef PROGRESS_P_H
#define PROGRESS_P_H

#include <QObject>

class Progress;

class ProgressPrivate
{
    Q_DISABLE_COPY(ProgressPrivate)
    Q_DECLARE_PUBLIC(Progress)

public:
    ProgressPrivate(Progress *q);
    ~ProgressPrivate();

    void init();

    Progress *const q_ptr;
};

#endif // PROGRESS_P_H
