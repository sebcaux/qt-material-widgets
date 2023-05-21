#ifndef QTMATERIALSWITCH_H
#define QTMATERIALSWITCH_H

#include "qtmaterialwidgets.h"

#include <QAbstractButton>

class QtMaterialSwitchPrivate;

class QTMATERIALWIDGETS_EXPORT QtMaterialSwitch : public QAbstractButton
{
    Q_OBJECT

    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
    Q_PROPERTY(QColor disabledColor READ disabledColor WRITE setDisabledColor)
    Q_PROPERTY(QColor activeColor READ activeColor WRITE setActiveColor)
    Q_PROPERTY(QColor inactiveColor READ inactiveColor WRITE setInactiveColor)
    Q_PROPERTY(QColor trackColor READ trackColor WRITE setTrackColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

public:
    explicit QtMaterialSwitch(QWidget *parent = nullptr);
    explicit QtMaterialSwitch(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~QtMaterialSwitch() override;

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor disabledColor() const;
    void setDisabledColor(const QColor &color);
    QColor activeColor() const;
    void setActiveColor(const QColor &color);
    QColor inactiveColor() const;
    void setInactiveColor(const QColor &color);
    QColor trackColor() const;
    void setTrackColor(const QColor &color);
    QColor textColor() const;
    void setTextColor(const QColor &color);

protected:
    const QScopedPointer<QtMaterialSwitchPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialSwitch)
    Q_DECLARE_PRIVATE(QtMaterialSwitch)

    // QWidget interface
public:
    QSize sizeHint() const override;

protected:
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALSWITCH_H
