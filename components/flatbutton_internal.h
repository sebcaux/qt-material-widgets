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
    Q_PROPERTY(qreal focusHaloOpacity WRITE setFocusHaloOpacity READ focusHaloOpacity)
    Q_PROPERTY(qreal focusHaloSize WRITE setFocusHaloSize READ focusHaloSize)

public:
    FlatButtonDelegate(FlatButton *parent);
    ~FlatButtonDelegate();

    void setBackgroundOpacity(qreal opacity);
    qreal backgroundOpacity() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setFocusHaloOpacity(qreal opacity);
    qreal focusHaloOpacity() const;

    void setFocusHaloSize(qreal size);
    qreal focusHaloSize() const;

    void updatePalette();

private:
    Q_DISABLE_COPY(FlatButtonDelegate)

    void addTransition(QEvent::Type eventType, QState *fromState, QState *toState);

    FlatButton *const  button;
    QState     *const _normalState;
    QState     *const _normalFocusedState;
    QState     *const _hoveredState;
    QState     *const _hoveredFocusedState;
    QState     *const _pressedState;
    qreal             _backgroundOpacity;
    qreal             _focusHaloOpacity;
    qreal             _focusHaloSize;
    QColor            _backgroundColor;
};

#endif // FLATBUTTON_INTERNAL_H
