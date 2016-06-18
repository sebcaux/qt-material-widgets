#ifndef CIRCULAR_PROGRESS_H
#define CIRCULAR_PROGRESS_H

#include <QWidget>

class CircularProgressPrivate;

class CircularProgress : public QWidget
{
    Q_OBJECT

public:
    explicit CircularProgress(QWidget *parent = 0);
    ~CircularProgress();

protected:
    const QScopedPointer<CircularProgressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(CircularProgress)
    Q_DECLARE_PRIVATE(CircularProgress)
};

#endif // CIRCULAR_PROGRESS_H
