#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>

class Slider : public QWidget
{
    Q_OBJECT

public:
    explicit Slider(QWidget *parent = 0);
    ~Slider();
};

#endif // SLIDER_H
