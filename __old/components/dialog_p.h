#ifndef DIALOG_P_H
#define DIALOG_P_H

#include <QObject>

class QStateMachine;
class Dialog;
class DialogWindow;
class TransparencyProxy;

class DialogPrivate
{
    Q_DISABLE_COPY(DialogPrivate)
    Q_DECLARE_PUBLIC(Dialog)

public:
    DialogPrivate(Dialog *q);

    void init();

    Dialog            *const q_ptr;
    QStateMachine     *const machine;
    DialogWindow      *const window;
    TransparencyProxy *const proxy;
};

#endif // DIALOG_P_H
