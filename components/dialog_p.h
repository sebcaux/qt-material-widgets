#ifndef DIALOG_P_H
#define DIALOG_P_H

#include <QObject>

class Dialog;
class DialogWindow;

class DialogPrivate
{
    Q_DISABLE_COPY(DialogPrivate)
    Q_DECLARE_PUBLIC(Dialog)

public:
    DialogPrivate(Dialog *q);

    void init();

    Dialog *const q_ptr;
    DialogWindow *window;
};

#endif // DIALOG_P_H
