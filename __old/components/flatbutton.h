#ifndef FLATBUTTON_H
#define FLATBUTTON_H

#include <QPushButton>
#include <QScopedPointer>
#include "lib/theme.h"

class FlatButtonPrivate;

class FlatButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(Material::Role role WRITE setRole READ role)
    Q_PROPERTY(Material::RippleStyle rippleStyle WRITE setRippleStyle READ rippleStyle)
    Q_PROPERTY(qreal cornerRadius WRITE setCornerRadius READ cornerRadius)
    Q_PROPERTY(Qt::BGMode backgroundMode WRITE setBackgroundMode READ backgroundMode)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor disabledTextColor WRITE setDisabledTextColor READ disabledTextColor)
    Q_PROPERTY(qreal peakOpacity WRITE setPeakOpacity READ peakOpacity)

public:
    explicit FlatButton(QWidget *parent = 0);
    explicit FlatButton(const QString &text, QWidget *parent = 0);
    ~FlatButton();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setHasFixedRippleRadius(bool value);
    bool hasFixedRippleRadius() const;

    void setFixedRippleRadius(qreal radius);

    void setRole(Material::Role role);
    Material::Role role() const;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setShowHalo(bool state);
    bool showHalo() const;

    void setRippleStyle(Material::RippleStyle style);
    Material::RippleStyle rippleStyle() const;

    void setIconPlacement(Material::IconPlacement placement);
    Material::IconPlacement iconPlacement() const;

    void setCornerRadius(qreal radius);
    qreal cornerRadius() const;

    void setBackgroundMode(Qt::BGMode mode);
    Qt::BGMode backgroundMode() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setDisabledTextColor(const QColor &color);
    QColor disabledTextColor() const;

    void setPeakOpacity(qreal opacity);
    qreal peakOpacity() const;

protected:
    FlatButton(FlatButtonPrivate &d, QWidget *parent = 0);

    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void paintHalo(QPainter *painter);

    const QScopedPointer<FlatButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(FlatButton)
    Q_DECLARE_PRIVATE(FlatButton)
};

#endif // FLATBUTTON_H
