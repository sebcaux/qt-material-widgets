#ifndef TOGGLE_INTERNAL_H
#define TOGGLE_INTERNAL_H

#include <QWidget>

class Toggle;

class ToggleThumb : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal shift WRITE setShift READ shift)
    Q_PROPERTY(QColor thumbColor WRITE setThumbColor READ thumbColor)

public:
    ToggleThumb(Toggle *parent);
    ~ToggleThumb();

    void setShift(qreal shift);
    inline qreal shift() const { return _shift; }

    inline qreal offset() const { return _offset; }

    inline void setThumbColor(const QColor &color)
    {
        _thumbColor = color;
        update();
    }

    inline QColor thumbColor() const
    {
        return _thumbColor;
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(ToggleThumb)

    void updateOffset();

    Toggle *const _toggle;
    qreal  _shift;
    qreal  _offset;
    QColor _thumbColor;
};

class ToggleTrack : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)

public:
    ToggleTrack(Toggle *parent);
    ~ToggleTrack();

    void setTrackColor(const QColor &color);

    inline QColor trackColor() const
    {
        return _trackColor;
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(ToggleTrack)

    Toggle *const _toggle;
    QColor _trackColor;
};

#endif // TOGGLE_INTERNAL_H
