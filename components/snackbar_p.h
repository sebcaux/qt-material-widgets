#ifndef SNACKBAR_P_H
#define SNACKBAR_P_H

#include <QObject>
#include <QColor>

class Snackbar;
class SnackbarStateMachine;

class SnackbarPrivate
{
    Q_DISABLE_COPY(SnackbarPrivate)
    Q_DECLARE_PUBLIC(Snackbar)

public:
    SnackbarPrivate(Snackbar *q);
    ~SnackbarPrivate();

    void init();

    Snackbar             *const q_ptr;
    SnackbarStateMachine *machine;
    QColor                backgroundColor;
    QColor                textColor;
    QList<QString>        messages;
    int                   duration;
    int                   boxWidth;
};

#endif // SNACKBAR_P_H
