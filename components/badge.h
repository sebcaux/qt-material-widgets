#ifndef BADGE_H
#define BADGE_H

#include <QWidget>

class BadgePrivate;

class Badge : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)

public:
    explicit Badge(QWidget *parent = 0);
    ~Badge();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setIcon(const QIcon &icon);
    void setText(const QString &text);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    int getDiameter() const;

    const QScopedPointer<BadgePrivate> d_ptr;

private:
    Q_DISABLE_COPY(Badge)
    Q_DECLARE_PRIVATE(Badge)
};

#endif // BADGE_H
