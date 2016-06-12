#ifndef PROGRESS_H
#define PROGRESS_H

#include <QWidget>

class Progress : public QWidget
{
    Q_OBJECT

public:
    explicit Progress(QWidget *parent = 0);
    ~Progress();

private:
    Q_DISABLE_COPY(Progress)
    //Q_DECLARE_PRIVATE(Progress)
};

#endif // PROGRESS_H
