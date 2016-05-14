#ifndef FLATBUTTON_H
#define FLATBUTTON_H

#include <QPushButton>

class FlatButton : public QPushButton
{
    Q_OBJECT

public:
    explicit FlatButton(QWidget *parent = 0);
    explicit FlatButton(const QString &text, QWidget *parent = 0);
    ~FlatButton();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};

#endif // FLATBUTTON_H

//#ifndef FLATBUTTON_H
//#define FLATBUTTON_H
//
//#include <QAbstractButton>
//#include <QStyleOptionButton>
//#include "../lib/rippleoverlay.h"
//
//class FlatButton : public QAbstractButton
//{
//    Q_OBJECT
//
//public:
//    explicit FlatButton(QWidget *parent = 0);
//    explicit FlatButton(const QString &text, QWidget *parent = 0);
//    ~FlatButton();
//
//    QSize sizeHint() const Q_DECL_OVERRIDE;
//
//protected:
//    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
//    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
//    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
//    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
//
//    QStyleOptionButton getStyleOption() const;
//
//private:
//    inline void updateOverlayGeometry()
//    {
//        if (_overlay) {
//            _overlay->setGeometry(rect());
//        }
//    }
//
//    RippleOverlay *const _overlay;
//};
//
//#endif // FLATBUTTON_H
//
