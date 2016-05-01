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

private:
    QLineEdit *const _edit;
    Slider    *const _slider;
};

#endif // SLIDEREXAMPLES_H
