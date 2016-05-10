#ifndef SLIDERTHUMB_H
#define SLIDERTHUMB_H

#include <QWidget>

class SliderPrivate;

class SliderThumb : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal haloSize WRITE setHaloSize READ haloSize)

    friend class SliderPrivate;
    explicit SliderThumb(SliderPrivate *slider);

public:
    ~SliderThumb();

    inline void setHaloSize(qreal size)
    {
        _haloSize = size;
        update();
    }

    inline qreal haloSize() const { return _haloSize; }

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Q_DISABLE_COPY(SliderThumb)

    QRectF thumbGeometry() const;

    SliderPrivate *const slider;
    qreal _haloSize;
};

#endif // SLIDERTHUMB_H
