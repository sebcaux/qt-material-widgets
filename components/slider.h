#ifndef SLIDER_H
#define SLIDER_H

#include <QAbstractSlider>
#include <QScopedPointer>

class SliderPrivate;

class Slider : public QAbstractSlider
{
    Q_OBJECT

    Q_PROPERTY(qreal haloScaleFactor WRITE setHaloScaleFactor READ haloScaleFactor)

public:
    explicit Slider(QWidget *parent = 0);
    ~Slider();

    void setHaloScaleFactor(qreal factor);
    qreal haloScaleFactor() const;

protected slots:
    void handleAction(int action);

protected:
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
