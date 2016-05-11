#ifndef SLIDEREXAMPLES_H
#define SLIDEREXAMPLES_H

#include "examplelist.h"

class QLineEdit;
class QSlider;
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
    void flip2();
    void updateSliderValue();
    void inv();
    void togglePageStepMode();
    void toggleEnabled();

private:
    QLineEdit *const _edit;
    QLineEdit *const _edit2;
    Slider    *const _slider;
    Slider    *const _slider2;
    Slider    *const _slider3;
    QSlider   *const __slider;
};

#endif // SLIDEREXAMPLES_H
