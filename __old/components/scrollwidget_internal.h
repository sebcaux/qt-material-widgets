#ifndef SCROLLBAR_INTERNAL_H
#define SCROLLBAR_INTERNAL_H

#include <QStateMachine>
#include "scrollwidget.h"

class ScrollBar;

class ScrollBarStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
    ScrollBarStateMachine(ScrollBar *parent);
    ~ScrollBarStateMachine();

    inline void setOpacity(qreal opacity) { _opacity = opacity; scrollBar->update(); }
    inline qreal opacity() const { return _opacity; }

private:
    Q_DISABLE_COPY(ScrollBarStateMachine)

    ScrollBar *const scrollBar;
    qreal            _opacity;
};

#endif // SCROLLBAR_INTERNAL_H

