#ifndef SNACKBAR_H
#define SNACKBAR_H

#include <QWidget>

class Snackbar : public QWidget
{
    Q_OBJECT

public:
    explicit Snackbar(QWidget *parent = 0);
    ~Snackbar();

private:
    Q_DISABLE_COPY(Snackbar)
    //Q_DECLARE_PRIVATE(Snackbar)
};

#endif // SNACKBAR_H
