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
    Q_PROPERTY(Material::ButtonType type READ type WRITE setType)
    Q_PROPERTY(qreal fontSize READ fontSize WRITE setFontSize)
    Q_PROPERTY(bool haloVisible READ isHaloVisible WRITE setHaloVisible)
    Q_PROPERTY(Material::OverlayStyle overlayStyle READ overlayStyle WRITE setOverlayStyle)
    Q_PROPERTY(Material::RippleStyle rippleStyle READ rippleStyle WRITE setRippleStyle)
    Q_PROPERTY(Material::ButtonIconPlacement iconPlacement READ iconPlacement WRITE setIconPlacement)
    Q_PROPERTY(qreal cornerRadius READ cornerRadius WRITE setCornerRadius)
    Q_PROPERTY(qreal baseOpacity READ baseOpacity WRITE setBaseOpacity)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)
    Q_PROPERTY(QColor disabledForegroundColor READ disabledForegroundColor WRITE setDisabledForegroundColor)
    Q_PROPERTY(QColor disabledBackgroundColor READ disabledBackgroundColor WRITE setDisabledBackgroundColor)

public:
    explicit QtMaterialFlatButton(QWidget *parent = nullptr);
    explicit QtMaterialFlatButton(const QString &text, Material::ButtonPreset preset = Material::ButtonTextDefault, QWidget *parent = nullptr);
    explicit QtMaterialFlatButton(const QIcon &icon, const QString &text, Material::ButtonPreset preset = Material::ButtonTextDefault, QWidget *parent = nullptr);
    ~QtMaterialFlatButton() override;

    void applyPreset(Material::ButtonPreset preset);

    Material::Role role() const;
    void setRole(Material::Role role);

    Material::ButtonType type() const;
    void setType(Material::ButtonType type);

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

    qreal baseOpacity() const;
    void setBaseOpacity(qreal opacity);

    void setCheckable(bool value);

    bool hasFixedRippleRadius() const;
    void setHasFixedRippleRadius(bool value);
    void setFixedRippleRadius(qreal radius);

    Qt::Alignment textAlignment() const;
    void setTextAlignment(Qt::Alignment alignment);

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

    QtMaterialFlatButton(QtMaterialFlatButtonPrivate &d, QWidget *parent = nullptr, Material::ButtonPreset preset = Material::ButtonTextDefault);

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
    bool event(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALFLATBUTTON_H
