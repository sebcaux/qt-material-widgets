#ifndef AVATAR_H
#define AVATAR_H

#include <QWidget>

class AvatarPrivate;

class Avatar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)

public:
    explicit Avatar(QWidget *parent = 0);
    explicit Avatar(const QIcon &icon, QWidget *parent = 0);
    explicit Avatar(const QChar &letter, QWidget *parent = 0);
    explicit Avatar(const QImage &image, QWidget *parent = 0);
    ~Avatar();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setSize(int size);
    int size() const;

    void setLetter(const QChar &letter);
    void setImage(const QImage &image);
    void setIcon(const QIcon &icon);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<AvatarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Avatar)
    Q_DECLARE_PRIVATE(Avatar)
};

#endif // AVATAR_H
