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
    Q_PROPERTY(Qt::BGMode bgMode WRITE setBgMode READ bgMode)
    Q_PROPERTY(QColor primaryBgColor WRITE setPrimaryBgColor READ primaryBgColor)
    Q_PROPERTY(QColor secondaryBgColor WRITE setSecondaryBgColor READ secondaryBgColor)
    Q_PROPERTY(QColor defaultBgColor WRITE setDefaultBgColor READ defaultBgColor)
    Q_PROPERTY(QColor primaryTextColor WRITE setPrimaryTextColor READ primaryTextColor)
    Q_PROPERTY(QColor secondaryTextColor WRITE setSecondaryTextColor READ secondaryTextColor)
    Q_PROPERTY(QColor defaultTextColor WRITE setDefaultTextColor READ defaultTextColor)
    Q_PROPERTY(QColor disabledTextColor WRITE setDisabledTextColor READ disabledTextColor)
    Q_PROPERTY(qreal peakOpacity WRITE setPeakOpacity READ peakOpacity)

public:
    explicit FlatButton(QWidget *parent = 0);
    explicit FlatButton(const QString &text, QWidget *parent = 0);
    ~FlatButton();

    void setRole(Material::Role role);
    Material::Role role() const;

    void setRippleStyle(Material::RippleStyle style);
    Material::RippleStyle rippleStyle() const;

    void setCornerRadius(qreal radius);
    qreal cornerRadius() const;

    void setBgMode(Qt::BGMode mode);
    Qt::BGMode bgMode() const;

    void setPrimaryBgColor(const QColor &color);
    QColor primaryBgColor() const;

    void setSecondaryBgColor(const QColor &color);
    QColor secondaryBgColor() const;

    void setDefaultBgColor(const QColor &color);
    QColor defaultBgColor() const;

    void setPrimaryTextColor(const QColor &color);
    QColor primaryTextColor() const;

    void setSecondaryTextColor(const QColor &color);
    QColor secondaryTextColor() const;

    void setDefaultTextColor(const QColor &color);
    QColor defaultTextColor() const;

    void setDisabledTextColor(const QColor &color);
    QColor disabledTextColor() const;

    void setPeakOpacity(qreal opacity);
    qreal peakOpacity() const;

protected:
    FlatButton(FlatButtonPrivate &d, QWidget *parent = 0);

    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<FlatButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(FlatButton)
    Q_DECLARE_PRIVATE(FlatButton)
};

#endif // FLATBUTTON_H
