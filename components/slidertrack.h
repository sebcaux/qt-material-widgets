#ifndef SLIDERTRACK_H
#define SLIDERTRACK_H

#include <QWidget>

class Slider;

class SliderTrack : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor fillColor WRITE setFillColor READ fillColor)
    Q_PROPERTY(int trackWidth WRITE setTrackWidth READ trackWidth)

public:
    explicit SliderTrack(Slider *slider);
    ~SliderTrack();

    inline void setFillColor(const QColor &color)
    {
        _fillColor = color;
        update();
    }

    inline QColor fillColor() const
    {
        return _fillColor;
    }

    void setTrackWidth(int width)
    {
        _width = width;
        update();
    }

    int trackWidth() const
    {
        return _width;
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Q_DISABLE_COPY(SliderTrack)

    const Slider *const slider;
    QColor _fillColor;
    int    _width;
};

#endif // SLIDERTRACK_H
