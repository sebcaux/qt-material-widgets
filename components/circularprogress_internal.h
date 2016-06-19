#ifndef CIRCULARPROGRESS_INTERNAL_H
#define CIRCULARPROGRESS_INTERNAL_H

#include <QObject>

class CircularProgress;

class CircularProgressDelegate : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal dashOffset WRITE setDashOffset READ dashOffset)
    Q_PROPERTY(qreal dashLength WRITE setDashLength READ dashLength)

public:
    CircularProgressDelegate(CircularProgress *parent);
    ~CircularProgressDelegate();

    void setDashOffset(qreal offset);
    qreal dashOffset() const;

    void setDashLength(qreal value);
    qreal dashLength() const;

private:
    Q_DISABLE_COPY(CircularProgressDelegate)

    CircularProgress *const progress;
    qreal _dashOffset;
    qreal _dashLength;
};

#endif // CIRCULARPROGRESS_INTERNAL_H
