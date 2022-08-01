#ifndef QTMATERIALAVATAR_H
#define QTMATERIALAVATAR_H

#include <QWidget>

#include "lib/qtmaterialtheme.h"

class QtMaterialAvatarPrivate;

class QtMaterialAvatar : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialAvatar(QWidget *parent = nullptr);
    explicit QtMaterialAvatar(const QIcon &icon, QWidget *parent = nullptr);
    explicit QtMaterialAvatar(const QChar &letter, QWidget *parent = nullptr);
    explicit QtMaterialAvatar(const QImage &image, QWidget *parent = nullptr);
    ~QtMaterialAvatar() override;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    QSize sizeHint() const override;

    void setSize(int size);
    int size() const;

    void setLetter(const QChar &letter);
    void setImage(const QImage &image);
    void setIcon(const QIcon &icon);

    Material::AvatarType type() const;

protected:
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<QtMaterialAvatarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialAvatar)
    Q_DECLARE_PRIVATE(QtMaterialAvatar)
};

#endif  // QTMATERIALAVATAR_H
