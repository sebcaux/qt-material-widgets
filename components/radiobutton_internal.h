#ifndef RADIOBUTTON_INTERNAL_H
#define RADIOBUTTON_INTERNAL_H

#include <QWidget>
#include <QIcon>

class QGraphicsColorizeEffect;

class RadioButtonIcon : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(int iconSize READ iconSize WRITE setIconSize)

public:
    RadioButtonIcon(const QIcon &icon, QWidget *parent = 0);
    ~RadioButtonIcon();

    inline void setIcon(const QIcon &icon) { _icon = icon; update(); }
    inline QIcon icon() const { return _icon; }

    void setColor(const QColor &color);
    QColor color() const;

    void setIconSize(int size);
    int iconSize() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(RadioButtonIcon)

    QIcon _icon;
    int   _iconSize;
    QGraphicsColorizeEffect *const _effect;
};

#endif // RADIOBUTTON_INTERNAL_H
