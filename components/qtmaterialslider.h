#ifndef QTMATERIALSLIDER_H
#define QTMATERIALSLIDER_H

#include "qtmaterialwidgets.h"

#include <QAbstractSlider>

#include <QScopedPointer>

#define QT_MATERIAL_SLIDER_MARGIN 30

class QtMaterialSliderPrivate;

class QTMATERIALWIDGETS_EXPORT QtMaterialSlider : public QAbstractSlider
{
    Q_OBJECT

    Q_PROPERTY(bool pageStepMode READ pageStepMode WRITE setPageStepMode)
    Q_PROPERTY(QColor thumbColor READ thumbColor WRITE setThumbColor)
    Q_PROPERTY(QColor trackColor READ trackColor WRITE setTrackColor)
    Q_PROPERTY(QColor disabledColor READ disabledColor WRITE setDisabledColor)

public:
    explicit QtMaterialSlider(QWidget *parent = nullptr);
    ~QtMaterialSlider() override;

    bool pageStepMode() const;
    void setPageStepMode(bool pageStep);

    void setInvertedAppearance(bool value);

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor thumbColor() const;
    void setThumbColor(const QColor &color);
    QColor trackColor() const;
    void setTrackColor(const QColor &color);
    QColor disabledColor() const;
    void setDisabledColor(const QColor &color);

protected:
    void updateThumbOffset();

    const QScopedPointer<QtMaterialSliderPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialSlider)
    Q_DECLARE_PRIVATE(QtMaterialSlider)

    // QWidget interface
public:
    QSize minimumSizeHint() const override;

protected:
    void sliderChange(SliderChange change) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
    bool event(QEvent *event) override;
};

#endif  // QTMATERIALSLIDER_H
