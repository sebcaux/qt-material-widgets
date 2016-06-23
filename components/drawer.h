#ifndef DRAWER_H
#define DRAWER_H

#include <QWidget>

class Drawer : public QWidget
{
    Q_OBJECT

public:
    explicit Drawer(QWidget *parent = 0);
    ~Drawer();

    Drawer *const q_ptr;

private:
    Q_DISABLE_COPY(Drawer)
    Q_DECLARE_PRIVATE(Drawer)
};

#endif // DRAWER_H
