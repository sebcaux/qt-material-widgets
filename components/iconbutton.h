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
    void setGeometryWidget(QWidget *widget);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

    QStyleOptionButton getStyleOption() const;

private:
    void updateOverlayGeometry();

    RippleOverlay *const _overlay;
    QWidget       *_geometryWidget;
};

#endif // ICONBUTTON_H
