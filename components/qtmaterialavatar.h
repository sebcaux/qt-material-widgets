#ifndef QTMATERIALAVATAR_H
#define QTMATERIALAVATAR_H

#include <QWidget>

#include "lib/qtmaterialtheme.h"

class QtMaterialAvatarPrivate;

class QtMaterialAvatar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    explicit QtMaterialAvatar(QWidget *parent = nullptr);
    explicit QtMaterialAvatar(const QIcon &icon, QWidget *parent = nullptr);
    explicit QtMaterialAvatar(const QChar &letter, QWidget *parent = nullptr);
    explicit QtMaterialAvatar(const QImage &image, QWidget *parent = nullptr);
    ~QtMaterialAvatar() override;

    const QChar &letter() const;
    void setLetter(const QChar &letter);
    const QImage &image() const;
    void setImage(const QImage &image);
    const QIcon &icon() const;
    void setIcon(const QIcon &icon);

    Material::AvatarType type() const;

    int size() const;
    void setSize(int size);

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor textColor() const;
    void setTextColor(const QColor &color);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

private:
    Q_DISABLE_COPY(QtMaterialAvatar)
    Q_DECLARE_PRIVATE(QtMaterialAvatar)

protected:
    const QScopedPointer<QtMaterialAvatarPrivate> d_ptr;

    // QWidget interface
public:
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALAVATAR_H
