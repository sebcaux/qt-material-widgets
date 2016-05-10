#ifndef SLIDERTHUMB_H
#define SLIDERTHUMB_H

#include <QWidget>

class Slider;
class SliderPrivate;

class SliderThumb : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal diameter WRITE setDiameter READ diameter)
    Q_PROPERTY(qreal borderWidth WRITE setBorderWidth READ borderWidth)
    Q_PROPERTY(QColor fillColor WRITE setFillColor READ fillColor)
    Q_PROPERTY(qreal haloSize WRITE setHaloSize READ haloSize)

    friend class SliderPrivate;
    explicit SliderThumb(Slider *slider);

public:
    ~SliderThumb();

    inline void setDiameter(qreal diameter)
    {
        _diameter = diameter;
        update();
    }

    inline qreal diameter() const
    {
        return _diameter;
    }

    inline void setBorderWidth(qreal width)
    {
        _borderWidth = width;
        update();
    }

    inline qreal borderWidth() const
    {
        return _borderWidth;
    }

    inline void setFillColor(const QColor &color)
    {
        _fillColor = color;
        update();
    }

    inline QColor fillColor() const
    {
        return _fillColor;
    }

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

    const Slider *const slider;
    qreal  _diameter;
    qreal  _borderWidth;
    QColor _fillColor;
    qreal  _haloSize;

};

#endif // SLIDERTHUMB_H
