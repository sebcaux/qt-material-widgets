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

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(Thumb)

    Toggle *const _toggle;
    qreal _shift;
    int _offset;
};

#endif // TOGGLE_INTERNAL_H
