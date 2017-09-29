#ifndef DIALOG_INTERNAL_H
#define DIALOG_INTERNAL_H

#include <QWidget>

class QStateMachine;
class Dialog;

class DialogWindow : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int offset WRITE setOffset READ offset)

public:
    explicit DialogWindow(Dialog *dialog, QWidget *parent = 0);
    ~DialogWindow();

    void setOffset(int offset);
    int offset() const;

signals:
    void dialogActivated();
    void dialogDeactivated();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(DialogWindow)

    Dialog *const dialog;
};

#endif // DIALOG_INTERNAL_H
