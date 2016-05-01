#ifndef SLIDER_H
#define SLIDER_H

#include <QAbstractSlider>
#include <QPoint>

class QPropertyAnimation;
class Slider;

class Handle : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal knobSize WRITE setKnobSize READ knobSize)

public:
    explicit Handle(Slider *slider);
    ~Handle();

    inline QSize sizeHint() const Q_DECL_OVERRIDE { return QSize(20, 20); }

    inline void setRelativePosition(const QPoint &pos) { setPosition(_offset + pos); }

    inline void setPosition(const QPoint &pos) { _position = pos; refreshGeometry(); }
    inline const QPoint &position() const { return _position; }

    inline void setOffset(const QPoint &offset) { _offset = offset; update(); }
    inline const QPoint &offset() const { return _offset; }

    inline void setKnobSize (qreal size ) { _knobSize = size; refreshGeometry(); }
    inline qreal knobSize() const { return _knobSize; }

    void refreshGeometry();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
//    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
//    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
//    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    Slider *const _slider;
    QPoint        _position;
    QPoint        _eventPos;
    QPoint        _offset;
    qreal         _knobSize;
};

class Slider : public QAbstractSlider
{
    Q_OBJECT

public:
    explicit Slider(QWidget *parent = 0);
    ~Slider();

    inline void setOrientation(Qt::Orientation orientation) { _orientation = orientation; }
    inline Qt::Orientation orientation() const { return _orientation; }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    friend class Handle;

    bool overTrack(const QPoint &pos) const;
    bool overHandle(const QPoint &pos) const;

    void updateValue();
    void updateHoverState(const QPoint &pos);

    QPropertyAnimation *const _animation;
    bool            _drag;
    bool            _hover;
    Handle   *const _handle;
    Qt::Orientation _orientation;
};

#endif // SLIDER_H
