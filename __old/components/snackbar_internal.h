#ifndef SNACKBAR_INTERNAL_H
#define SNACKBAR_INTERNAL_H

#include <QStateMachine>
#include <QTimer>

class Snackbar;

class SnackbarStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal offset WRITE setOffset READ offset)

public:
    SnackbarStateMachine(Snackbar *parent);
    ~SnackbarStateMachine();

    void setOffset(qreal offset);
    qreal offset() const;

protected slots:
    void snackbarHidden();
    void snackbarShown();

signals:
    void showSnackbar();
    void hideSnackbar();
    void waitForSnackbar();
    void showNextSnackbar();

private:
    Q_DISABLE_COPY(SnackbarStateMachine)

    Snackbar *const snackbar;
    QTimer          _timer;
    qreal           _offset;
};

#endif // SNACKBAR_INTERNAL_H
