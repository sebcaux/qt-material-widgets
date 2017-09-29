#ifndef FLATBUTTON_INTERNAL_H
#define FLATBUTTON_INTERNAL_H

#include <QStateMachine>
#include <QColor>

class QPropertyAnimation;
class FlatButton;

class FlatButtonDelegate : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(qreal backgroundOpacity WRITE setBackgroundOpacity READ backgroundOpacity)
    Q_PROPERTY(qreal haloOpacity WRITE setHaloOpacity READ haloOpacity)
    Q_PROPERTY(qreal haloSize WRITE setHaloSize READ haloSize)
    Q_PROPERTY(qreal haloScaleFactor WRITE setHaloScaleFactor READ haloScaleFactor)

public:
    FlatButtonDelegate(FlatButton *parent);
    ~FlatButtonDelegate();

    void setBackgroundOpacity(qreal opacity);
    qreal backgroundOpacity() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setHaloOpacity(qreal opacity);
    qreal haloOpacity() const;

    void setHaloSize(qreal size);
    qreal haloSize() const;

    void setHaloScaleFactor(qreal size);
    qreal haloScaleFactor() const;

    void updatePalette();

signals:
    void pressed();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Q_DISABLE_COPY(FlatButtonDelegate)

    void addTransition(QObject *object, const char *signal, QState *fromState, QState *toState);
    void addTransition(QObject *object, QEvent::Type eventType, QState *fromState, QState *toState);
    void addTransition(QAbstractTransition *transition, QState *fromState, QState *toState);

    FlatButton *const  button;
    QState     *const _normalState;
    QState     *const _normalFocusedState;
    QState     *const _hoveredState;
    QState     *const _hoveredFocusedState;
    QState     *const _pressedState;
    qreal             _backgroundOpacity;
    qreal             _haloOpacity;
    qreal             _haloSize;
    qreal             _haloScaleFactor;
    QColor            _backgroundColor;
};

#endif // FLATBUTTON_INTERNAL_H
