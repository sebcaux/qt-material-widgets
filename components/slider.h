#ifndef SLIDER_H
#define SLIDER_H

#include <QAbstractSlider>
#include <QScopedPointer>

class SliderPrivate;

class Slider : public QAbstractSlider
{
    Q_OBJECT

    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)

public:
    explicit Slider(QWidget *parent = 0);
    ~Slider();

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    int thumbOffset() const;

    void setPageStepMode(bool pageStep);
    bool pageStepMode() const;

    void setTrackColor(const QColor &color);
    QColor trackColor() const;

signals:
    void changedToMinimum();
    void changedFromMinimum();
    void sliderEnabled();
    void sliderDisabled();

protected:
    void sliderChange(SliderChange change) Q_DECL_OVERRIDE;

    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<SliderPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Slider)
    Q_DECLARE_PRIVATE(Slider)
};

#endif // SLIDER_H
