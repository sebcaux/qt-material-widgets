#ifndef SLIDEREXAMPLES_H
#define SLIDEREXAMPLES_H

#include "examplelist.h"

class QLineEdit;

class SliderExamples : public ExampleList
{
    Q_OBJECT

public:
    explicit SliderExamples(QWidget *parent = 0);
    ~SliderExamples();

protected slots:
    void updateValue(int value);

private:
    QLineEdit *const _edit;
};

#endif // SLIDEREXAMPLES_H
