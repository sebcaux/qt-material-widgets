#ifndef DIALOG_INTERNAL_H
#define DIALOG_INTERNAL_H

#include <QWidget>

class Dialog;

class DialogWindow : public QWidget
{
    Q_OBJECT

public:
    DialogWindow(Dialog *parent);
    ~DialogWindow();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(DialogWindow)

    Dialog *const dialog;
};

#endif // DIALOG_INTERNAL_H
