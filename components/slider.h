#ifndef SLIDER_H
#define SLIDER_H

#include <QAbstractSlider>
#include <QScopedPointer>

class SliderPrivate;

class Slider : public QAbstractSlider
{
    Q_OBJECT

    Q_PROPERTY(int trackWidth WRITE setTrackWidth READ trackWidth)

public:
    explicit Slider(QWidget *parent = 0);
    ~Slider();

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    int thumbOffset() const;

    void setPageStepMode(bool pageStep);
    bool pageStepMode() const;

    void setTrackWidth(int width);
    int trackWidth() const;

signals:
    void changedToMinimum();       // @TODO: create custom event type
    void changedFromMinimum();     // @TODO: create custom event type
    void sliderEnabled();          //
    void sliderDisabled();         //
    void mouseEnter();             //
    void mouseLeave();             //

protected:
    void sliderChange(SliderChange change) Q_DECL_OVERRIDE;

    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;
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
