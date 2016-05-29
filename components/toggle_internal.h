#ifndef TOGGLE_INTERNAL_H
#define TOGGLE_INTERNAL_H

#include <QWidget>

class Toggle;

class Thumb : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal shift WRITE setShift READ shift)

public:
    Thumb(Toggle *parent);
    ~Thumb();

    void setShift(qreal shift);
    inline qreal shift() const { return _shift; }

    inline qreal offset() const { return _offset; }

signals:
    void clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(Thumb)

    Toggle *const _toggle;
    qreal _shift;
    qreal _offset;
};

#endif // TOGGLE_INTERNAL_H
