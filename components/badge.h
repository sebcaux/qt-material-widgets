#ifndef BADGE_H
#define BADGE_H

#include <QWidget>

class Badge : public QWidget
{
    Q_OBJECT

public:
    explicit Badge(QWidget *parent = 0);
    ~Badge();

private:
    Q_DISABLE_COPY(Badge)
    //Q_DECLARE_PRIVATE(Badge)
};

#endif // BADGE_H
