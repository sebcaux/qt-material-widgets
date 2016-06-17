#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>

class Dialog : public QWidget
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Q_DISABLE_COPY(Dialog)
    //Q_DECLARE_PRIVATE(Dialog)
};

#endif // DIALOG_H
