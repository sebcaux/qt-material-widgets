#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>

class Handle : public QWidget
{
    Q_OBJECT

public:
    explicit Handle(QWidget *parent = 0);
    ~Handle();

protected:
    void paintEvent(QPaintEvent *event);
};

class Slider : public QWidget
{
    Q_OBJECT

public:
    explicit Slider(QWidget *parent = 0);
    ~Slider();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Handle *const _handle;
};

#endif // SLIDER_H
