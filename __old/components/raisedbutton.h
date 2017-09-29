#ifndef RAISEDBUTTON_H
#define RAISEDBUTTON_H

#include "flatbutton.h"

class RaisedButtonPrivate;

class RaisedButton : public FlatButton
{
    Q_OBJECT

    Q_PROPERTY(QColor disabledBackgroundColor WRITE setDisabledBackgroundColor READ disabledBackgroundColor)

public:
    explicit RaisedButton(QWidget *parent = 0);
    ~RaisedButton();

    void setDisabledBackgroundColor(const QColor &color);
    QColor disabledBackgroundColor() const;

protected:
    RaisedButton(RaisedButtonPrivate &d, QWidget *parent = 0);

    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(RaisedButton)
    Q_DECLARE_PRIVATE(RaisedButton)
};

#endif // RAISEDBUTTON_H
