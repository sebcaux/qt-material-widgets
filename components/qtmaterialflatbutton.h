#ifndef QTMATERIALFLATBUTTON_H
#define QTMATERIALFLATBUTTON_H

#include <QPushButton>

#include "lib/qtmaterialtheme.h"

#include <QScopedPointer>

class QtMaterialFlatButtonPrivate;

class QtMaterialFlatButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(QColor foregroundColor WRITE setForegroundColor READ foregroundColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor overlayColor WRITE setOverlayColor READ overlayColor)
    Q_PROPERTY(QColor disabledForegroundColor WRITE setDisabledForegroundColor READ disabledForegroundColor)
    Q_PROPERTY(QColor disabledBackgroundColor WRITE setDisabledBackgroundColor READ disabledBackgroundColor)
    Q_PROPERTY(qreal fontSize WRITE setFontSize READ fontSize)

public:
    explicit QtMaterialFlatButton(QWidget *parent = nullptr, Material::ButtonPreset preset = Material::FlatPreset);
    explicit QtMaterialFlatButton(const QString &text, QWidget *parent = nullptr, Material::ButtonPreset preset = Material::FlatPreset);
    QtMaterialFlatButton(const QString &text, Material::Role role, QWidget *parent = nullptr, Material::ButtonPreset preset = Material::FlatPreset);
    ~QtMaterialFlatButton() override;

    void applyPreset(Material::ButtonPreset preset);

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setRole(Material::Role role);
    Material::Role role() const;

    void setForegroundColor(const QColor &color);
    QColor foregroundColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setOverlayColor(const QColor &color);
    QColor overlayColor() const;

    void setDisabledForegroundColor(const QColor &color);
    QColor disabledForegroundColor() const;

    void setDisabledBackgroundColor(const QColor &color);
    QColor disabledBackgroundColor() const;

    void setFontSize(qreal size);
    qreal fontSize() const;

    void setHaloVisible(bool visible);
    bool isHaloVisible() const;

    void setOverlayStyle(Material::OverlayStyle style);
    Material::OverlayStyle overlayStyle() const;

    void setRippleStyle(Material::RippleStyle style);
    Material::RippleStyle rippleStyle() const;

    void setIconPlacement(Material::ButtonIconPlacement placement);
    Material::ButtonIconPlacement iconPlacement() const;

    void setCornerRadius(qreal radius);
    qreal cornerRadius() const;

    void setBackgroundMode(Qt::BGMode mode);
    Qt::BGMode backgroundMode() const;

    void setBaseOpacity(qreal opacity);
    qreal baseOpacity() const;

    void setCheckable(bool value);

    void setHasFixedRippleRadius(bool value);
    bool hasFixedRippleRadius() const;

    void setFixedRippleRadius(qreal radius);

    void setTextAlignment(Qt::Alignment alignment);
    Qt::Alignment textAlignment() const;

    QSize sizeHint() const override;

protected:
    enum
    {
        IconPadding = 12
    };

    QtMaterialFlatButton(QtMaterialFlatButtonPrivate &d, QWidget *parent = nullptr, Material::ButtonPreset preset = Material::FlatPreset);

    void checkStateSet() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    virtual void paintBackground(QPainter *painter);
    virtual void paintHalo(QPainter *painter);
    virtual void paintForeground(QPainter *painter);

    virtual void updateClipPath();

    const QScopedPointer<QtMaterialFlatButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialFlatButton)
    Q_DECLARE_PRIVATE(QtMaterialFlatButton)
};

#endif  // QTMATERIALFLATBUTTON_H
