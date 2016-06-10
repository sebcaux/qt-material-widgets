#ifndef SLIDER_H
#define SLIDER_H

#include <QAbstractSlider>
#include <QScopedPointer>

#define SLIDER_MARGIN 30

class SliderPrivate;

class Slider : public QAbstractSlider
{
    Q_OBJECT

    Q_PROPERTY(QColor thumbColor WRITE setThumbColor READ thumbColor)
    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)
    Q_PROPERTY(QColor disabledColor WRITE setDisabledColor READ disabledColor)

public:
    explicit Slider(QWidget *parent = 0);
    ~Slider();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setThumbColor(const QColor &color);
    QColor thumbColor() const;

    void setTrackColor(const QColor &color);
    QColor trackColor() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    int thumbOffset() const;

    void setPageStepMode(bool pageStep);
    bool pageStepMode() const;

    bool hovered() const;

protected:
    void sliderChange(SliderChange change) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<SliderPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Slider)
    Q_DECLARE_PRIVATE(Slider)
};

#endif // SLIDER_H
