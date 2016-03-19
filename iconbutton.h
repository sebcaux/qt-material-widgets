#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QAbstractButton>
#include <QStyleOptionButton>

class RippleOverlay;

class IconButton : public QAbstractButton
{
    Q_OBJECT

public:
    explicit IconButton(const QIcon &icon, QWidget *parent = 0);
    ~IconButton();

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    void moveEvent(QMoveEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
    void updateOverlayGeometry();
    QStyleOptionButton getStyleOption() const;

    RippleOverlay *const _overlay;
};

#endif // ICONBUTTON_H
