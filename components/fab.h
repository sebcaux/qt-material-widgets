#ifndef FAB_H
#define FAB_H

#include "raisedbutton.h"

class FloatingActionButtonPrivate;

class FloatingActionButton : public RaisedButton
{
    Q_OBJECT

public:
    explicit FloatingActionButton(QWidget *parent = 0);
    ~FloatingActionButton();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setMini(bool state);
    bool isMini() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(FloatingActionButton)
    Q_DECLARE_PRIVATE(FloatingActionButton)
};

#endif // FAB_H
