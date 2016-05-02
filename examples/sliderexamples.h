#ifndef SLIDEREXAMPLES_H
#define SLIDEREXAMPLES_H

#include "examplelist.h"

class QLineEdit;
class Slider;

class SliderExamples : public ExampleList
{
    Q_OBJECT

public:
    explicit SliderExamples(QWidget *parent = 0);
    ~SliderExamples();

protected slots:
    void updateValue(int value);
    void flip();
    void updateSliderValue();

private:
    QLineEdit *const _edit;
    QLineEdit *const _edit2;
    Slider    *const _slider;
    Slider    *const _slider2;
};

#endif // SLIDEREXAMPLES_H
