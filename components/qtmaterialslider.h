#ifndef QTMATERIALSLIDER_H
#define QTMATERIALSLIDER_H

#include <QAbstractSlider>

#include <QScopedPointer>

#define QT_MATERIAL_SLIDER_MARGIN 30

class QtMaterialSliderPrivate;

class QtMaterialSlider : public QAbstractSlider
{
    Q_OBJECT

    Q_PROPERTY(QColor thumbColor WRITE setThumbColor READ thumbColor)
    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)
    Q_PROPERTY(QColor disabledColor WRITE setDisabledColor READ disabledColor)

public:
    explicit QtMaterialSlider(QWidget *parent = nullptr);
    ~QtMaterialSlider() override;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setThumbColor(const QColor &color);
    QColor thumbColor() const;

    void setTrackColor(const QColor &color);
    QColor trackColor() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

    void setPageStepMode(bool pageStep);
    bool pageStepMode() const;

    QSize minimumSizeHint() const override;

    void setInvertedAppearance(bool value);

protected:
    void sliderChange(SliderChange change) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;

    void updateThumbOffset();

    const QScopedPointer<QtMaterialSliderPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialSlider)
    Q_DECLARE_PRIVATE(QtMaterialSlider)
};

#endif  // QTMATERIALSLIDER_H
