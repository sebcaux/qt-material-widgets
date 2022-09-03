#ifndef QTMATERIALFLATBUTTON_H
#define QTMATERIALFLATBUTTON_H

#include <QPushButton>

#include "lib/qtmaterialtheme.h"

#include <QScopedPointer>

class QtMaterialFlatButtonPrivate;

class QtMaterialFlatButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(Material::Role role READ role WRITE setRole)
    Q_PROPERTY(qreal fontSize READ fontSize WRITE setFontSize)
    Q_PROPERTY(bool haloVisible READ isHaloVisible WRITE setHaloVisible)
    Q_PROPERTY(Material::OverlayStyle overlayStyle READ overlayStyle WRITE setOverlayStyle)
    Q_PROPERTY(Material::RippleStyle rippleStyle READ rippleStyle WRITE setRippleStyle)
    Q_PROPERTY(Material::ButtonIconPlacement iconPlacement READ iconPlacement WRITE setIconPlacement)
    Q_PROPERTY(qreal cornerRadius READ cornerRadius WRITE setCornerRadius)
    Q_PROPERTY(Qt::BGMode backgroundMode READ backgroundMode WRITE setBackgroundMode)
    Q_PROPERTY(qreal baseOpacity READ baseOpacity WRITE setBaseOpacity)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)
    Q_PROPERTY(QColor disabledForegroundColor READ disabledForegroundColor WRITE setDisabledForegroundColor)
    Q_PROPERTY(QColor disabledBackgroundColor READ disabledBackgroundColor WRITE setDisabledBackgroundColor)

public:
    explicit QtMaterialFlatButton(QWidget *parent = nullptr, Material::ButtonPreset preset = Material::FlatPreset);
    explicit QtMaterialFlatButton(const QString &text, QWidget *parent = nullptr, Material::ButtonPreset preset = Material::FlatPreset);
    QtMaterialFlatButton(const QString &text, Material::Role role, QWidget *parent = nullptr, Material::ButtonPreset preset = Material::FlatPreset);
    ~QtMaterialFlatButton() override;

    Material::Role role() const;
    void setRole(Material::Role role);

    qreal fontSize() const;
    void setFontSize(qreal size);

    bool isHaloVisible() const;
    void setHaloVisible(bool visible);

    Material::OverlayStyle overlayStyle() const;
    void setOverlayStyle(Material::OverlayStyle style);

    Material::RippleStyle rippleStyle() const;
    void setRippleStyle(Material::RippleStyle style);

    Material::ButtonIconPlacement iconPlacement() const;
    void setIconPlacement(Material::ButtonIconPlacement placement);

    qreal cornerRadius() const;
    void setCornerRadius(qreal radius);

    Qt::BGMode backgroundMode() const;
    void setBackgroundMode(Qt::BGMode mode);

    qreal baseOpacity() const;
    void setBaseOpacity(qreal opacity);

    void setCheckable(bool value);

    bool hasFixedRippleRadius() const;
    void setHasFixedRippleRadius(bool value);
    void setFixedRippleRadius(qreal radius);

    Qt::Alignment textAlignment() const;
    void setTextAlignment(Qt::Alignment alignment);

    void applyPreset(Material::ButtonPreset preset);

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor foregroundColor() const;
    void setForegroundColor(const QColor &color);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);
    QColor overlayColor() const;
    void setOverlayColor(const QColor &color);
    QColor disabledForegroundColor() const;
    void setDisabledForegroundColor(const QColor &color);
    QColor disabledBackgroundColor() const;
    void setDisabledBackgroundColor(const QColor &color);

protected:
    enum
    {
        IconPadding = 12
    };

    QtMaterialFlatButton(QtMaterialFlatButtonPrivate &d, QWidget *parent = nullptr, Material::ButtonPreset preset = Material::FlatPreset);

    virtual void paintBackground(QPainter *painter);
    virtual void paintHalo(QPainter *painter);
    virtual void paintForeground(QPainter *painter);

    virtual void updateClipPath();

    const QScopedPointer<QtMaterialFlatButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialFlatButton)
    Q_DECLARE_PRIVATE(QtMaterialFlatButton)

public:
    QSize sizeHint() const override;

    // QAbstractButton interface
protected:
    void checkStateSet() override;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALFLATBUTTON_H
