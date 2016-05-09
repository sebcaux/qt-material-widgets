#ifndef SLIDER_H
#define SLIDER_H

#include <QAbstractSlider>
#include <QScopedPointer>

class SliderPrivate;

class Slider : public QAbstractSlider
{
    Q_OBJECT

    Q_PROPERTY(qreal thumbSize WRITE setThumbSize READ thumbSize)
    Q_PROPERTY(qreal thumbPenWidth WRITE setThumbPenWidth READ thumbPenWidth)
    Q_PROPERTY(QColor thumbColor WRITE setThumbColor READ thumbColor)

public:
    explicit Slider(QWidget *parent = 0);
    ~Slider();

    QSize minimumSizeHint() const;

    int thumbOffset() const;

    void setThumbSize(qreal size);
    qreal thumbSize() const;

    void setThumbPenWidth(qreal width);
    qreal thumbPenWidth() const;

    void setThumbColor(const QColor &color);
    QColor thumbColor() const;

signals:
    void changedToMinimum();
    void changedFromMinimum();

protected:
    void sliderChange(SliderChange change) Q_DECL_OVERRIDE;

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
