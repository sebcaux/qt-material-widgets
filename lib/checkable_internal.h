#ifndef CHECKABLE_INTERNAL_H
#define CHECKABLE_INTERNAL_H

#include <QWidget>
#include <QIcon>

class QGraphicsColorizeEffect;

class CheckableIcon : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(qreal iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    CheckableIcon(const QIcon &icon, QWidget *parent = 0);
    ~CheckableIcon();

    inline void setIcon(const QIcon &icon) { _icon = icon; update(); }
    inline QIcon icon() const { return _icon; }

    void setColor(const QColor &color);
    QColor color() const;

    void setIconSize(qreal size);
    qreal iconSize() const;

    void setOpacity(qreal opacity);
    qreal opacity() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(CheckableIcon)

    QGraphicsColorizeEffect *const _effect;
    QIcon _icon;
    qreal _iconSize;
    qreal _opacity;
};

#endif // CHECKABLE_INTERNAL_H
