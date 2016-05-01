#ifndef SLIDER_H
#define SLIDER_H

#include <QAbstractSlider>
#include <QScopedPointer>

class SliderPrivate;

class Slider : public QAbstractSlider
{
    Q_OBJECT

public:
    explicit Slider(QWidget *parent = 0);
    ~Slider();

    void setOrientation(Qt::Orientation orientation);
    Qt::Orientation orientation() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<SliderPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Slider)
    Q_DECLARE_PRIVATE(Slider)
};

#endif // SLIDER_H
