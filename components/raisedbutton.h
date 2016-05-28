#ifndef RAISEDBUTTON_H
#define RAISEDBUTTON_H

#include "flatbutton.h"

class RaisedButtonPrivate;

class RaisedButton : public FlatButton
{
    Q_OBJECT

public:
    explicit RaisedButton(QWidget *parent = 0);
    ~RaisedButton();

    void setRole(Material::Role role) Q_DECL_OVERRIDE;

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(RaisedButton)
    Q_DECLARE_PRIVATE(RaisedButton)
};

#endif // RAISEDBUTTON_H
