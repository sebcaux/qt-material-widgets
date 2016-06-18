#ifndef CIRCULARPROGRESS_P_H
#define CIRCULARPROGRESS_P_H

#include <QObject>

class CircularProgress;

class CircularProgressPrivate
{
    Q_DISABLE_COPY(CircularProgressPrivate)
    Q_DECLARE_PUBLIC(CircularProgress)

public:
    CircularProgressPrivate(CircularProgress *q);
    ~CircularProgressPrivate();

    void init();

    CircularProgress *const q_ptr;
};

#endif // CIRCULARPROGRESS_P_H
