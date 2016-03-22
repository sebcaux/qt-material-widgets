#ifndef RAISEDBUTTON_H
#define RAISEDBUTTON_H

#include <QParallelAnimationGroup>
#include "flatbutton.h"

class QPropertyAnimation;

class RaisedButton : public FlatButton
{
    Q_OBJECT

public:
    explicit RaisedButton(QWidget *parent = 0);
    ~RaisedButton();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QParallelAnimationGroup _group;
};

#endif // RAISEDBUTTON_H
