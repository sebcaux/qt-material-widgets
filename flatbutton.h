#ifndef FLATBUTTON_H
#define FLATBUTTON_H

#include <QAbstractButton>
#include "rippleoverlay.h"

class FlatButton : public QAbstractButton
{
    Q_OBJECT

public:
    explicit FlatButton(QWidget *parent = 0);
    explicit FlatButton(const QString &text, QWidget *parent = 0);
    ~FlatButton();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;

private:
    inline void updateOverlayGeometry() { _overlay->setGeometry(rect()); }

    RippleOverlay *const _overlay;
};

#endif // FLATBUTTON_H
