#ifndef CIRCULARPROGRESS_INTERNAL_H
#define CIRCULARPROGRESS_INTERNAL_H

#include <QObject>
#include "circularprogress.h"

class CircularProgressDelegate : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal dashOffset WRITE setDashOffset READ dashOffset)
    Q_PROPERTY(qreal dashLength WRITE setDashLength READ dashLength)
    Q_PROPERTY(int angle WRITE setAngle READ angle)

public:
    CircularProgressDelegate(CircularProgress *parent);
    ~CircularProgressDelegate();

    inline void setDashOffset(qreal offset) { _dashOffset = offset; progress->update(); }
    inline qreal dashOffset() const { return _dashOffset; }

    inline void setDashLength(qreal value) { _dashLength = value; progress->update(); }
    inline qreal dashLength() const { return _dashLength; }

    inline void setAngle(int angle) { _angle = angle; progress->update(); }
    inline int angle() const { return _angle; }

private:
    Q_DISABLE_COPY(CircularProgressDelegate)

    CircularProgress *const progress;
    qreal _dashOffset;
    qreal _dashLength;
    int   _angle;
};

#endif // CIRCULARPROGRESS_INTERNAL_H
