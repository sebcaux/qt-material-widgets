#ifndef SLIDERINTERNAL_H
#define SLIDERINTERNAL_H

#include <QWidget>
#include <QStateMachine>

class Slider;
class SliderThumb;
class SliderTrack;

class SliderStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    SliderStateMachine(Slider *parent, SliderThumb *thumb, SliderTrack *track);
    ~SliderStateMachine();

    void updatePalette();

signals:
    void changedToMinimum();
    void changedFromMinimum();
    void noFocusMouseEnter();
    void noFocusMouseLeave();

private:
    Q_DISABLE_COPY(SliderStateMachine)

    Slider       *const slider;
    SliderTrack  *const _track;
    SliderThumb  *const _thumb;
    QState       *const _topState;
    QState       *const _fstState;
    QState       *const _inactiveState;
    QState       *const _focusState;
    QState       *const _slidingState;
    QState       *const _pulseOutState;
    QState       *const _pulseInState;
    QState       *const _sndState;
    QState       *const _minState;
    QState       *const _normalState;

};

class SliderThumb : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal diameter WRITE setDiameter READ diameter)
    Q_PROPERTY(qreal borderWidth WRITE setBorderWidth READ borderWidth)
    Q_PROPERTY(QColor borderColor WRITE setBorderColor READ borderColor)
    Q_PROPERTY(QColor fillColor WRITE setFillColor READ fillColor)
    Q_PROPERTY(qreal haloSize WRITE setHaloSize READ haloSize)
    Q_PROPERTY(QColor haloColor WRITE setHaloColor READ haloColor)

public:
    explicit SliderThumb(Slider *slider);
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

    inline void setBorderColor(const QColor &color)
    {
        _borderColor = color;
        update();
    }

    inline QColor borderColor() const
    {
        return _borderColor;
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

    inline qreal haloSize() const
    {
        return _haloSize;
    }

    inline void setHaloColor(const QColor &color)
    {
        _haloColor = color;
        update();
    }

    inline QColor haloColor() const
    {
        return _haloColor;
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Q_DISABLE_COPY(SliderThumb)

    const Slider *const slider;
    qreal  _diameter;
    qreal  _borderWidth;
    qreal  _haloSize;
    QColor _borderColor;
    QColor _fillColor;
    QColor _haloColor;
};

class SliderTrack : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor fillColor WRITE setFillColor READ fillColor)

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
        _trackWidth = width;
        update();
    }

    int trackWidth() const
    {
        return _trackWidth;
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Q_DISABLE_COPY(SliderTrack)

    const Slider *const slider;
    QColor _fillColor;
    int    _trackWidth;
};

#endif // SLIDERINTERNAL_H
