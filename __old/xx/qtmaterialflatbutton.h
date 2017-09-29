#ifndef QTMATERIALFLATBUTTON_H
#define QTMATERIALFLATBUTTON_H

#include <QPushButton>
#include <QScopedPointer>
#include "xxlib/qtmaterialtheme.h"

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
    explicit QtMaterialFlatButton(QWidget *parent = 0, XXMaterial::ButtonPreset preset = XXMaterial::FlatPreset);
    explicit QtMaterialFlatButton(const QString &text, QWidget *parent = 0, XXMaterial::ButtonPreset preset = XXMaterial::FlatPreset);
    QtMaterialFlatButton(const QString &text, XXMaterial::Role role, QWidget *parent = 0, XXMaterial::ButtonPreset preset = XXMaterial::FlatPreset);
    ~QtMaterialFlatButton();

    void applyPreset(XXMaterial::ButtonPreset preset);

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setRole(XXMaterial::Role role);
    XXMaterial::Role role() const;

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

    void setOverlayStyle(XXMaterial::OverlayStyle style);
    XXMaterial::OverlayStyle overlayStyle() const;

    void setRippleStyle(XXMaterial::RippleStyle style);
    XXMaterial::RippleStyle rippleStyle() const;

    void setIconPlacement(XXMaterial::ButtonIconPlacement placement);
    XXMaterial::ButtonIconPlacement iconPlacement() const;

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

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    enum {
        IconPadding = 12
    };

    QtMaterialFlatButton(QtMaterialFlatButtonPrivate &d, QWidget *parent = 0, XXMaterial::ButtonPreset preset = XXMaterial::FlatPreset);

    void checkStateSet() Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    virtual void paintBackground(QPainter *painter);
    virtual void paintHalo(QPainter *painter);
    virtual void paintForeground(QPainter *painter);

    virtual void updateClipPath();

    const QScopedPointer<QtMaterialFlatButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialFlatButton)
    Q_DECLARE_PRIVATE(QtMaterialFlatButton)
};

#endif // QTMATERIALFLATBUTTON_H
