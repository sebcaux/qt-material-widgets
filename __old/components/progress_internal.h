#ifndef PROGRESS_INTERNAL_H
#define PROGRESS_INTERNAL_H

#include <QObject>

class Progress;

class ProgressDelegate : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal offset WRITE setOffset READ offset)

public:
    ProgressDelegate(Progress *parent);
    ~ProgressDelegate();

    void setOffset(qreal offset);
    qreal offset() const;

private:
    Q_DISABLE_COPY(ProgressDelegate)

    Progress *const progress;
    qreal _offset;
};

#endif // PROGRESS_INTERNAL_H
