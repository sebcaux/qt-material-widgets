#ifndef TOGGLE_INTERNAL_H
#define TOGGLE_INTERNAL_H

#include <QWidget>

class Toggle;

class Thumb : public QWidget
{
    Q_OBJECT

public:
    Thumb(Toggle *parent);
    ~Thumb();

private:
    Q_DISABLE_COPY(Thumb)
};

#endif // TOGGLE_INTERNAL_H
