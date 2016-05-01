#include <QDebug>
#include <QVBoxLayout>
#include <QLineEdit>
#include "sliderexamples.h"
#include "components/slider.h"
#include "exampleview.h"
#include "frame.h"

SliderExamples::SliderExamples(QWidget *parent)
    : ExampleList(parent),
      _edit(new QLineEdit)
{
    QLayout *mainLayout = widget()->layout();

    {
        Slider *slider = new Slider;
        slider->setMinimumWidth(250);

        ExampleView *view = new ExampleView;
        view->setWidget(slider);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "Slider *slider = new Slider;"
        );
        frame->setWidget(view);

        mainLayout->addWidget(frame);
    }
    {
        Slider *slider = new Slider;
        slider->setOrientation(Qt::Vertical);

        ExampleView *view = new ExampleView;
        view->setWidget(slider);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "Slider *slider = new Slider;\n"
            "slider->setOrientation(Qt::Vertical);"
        );
        frame->setWidget(view);

        mainLayout->addWidget(frame);
    }
    {
        QWidget *widget = new QWidget;
        QHBoxLayout *layout = new QHBoxLayout;

        widget->setLayout(layout);

        Slider *slider = new Slider;

        layout->addWidget(slider);
        layout->addWidget(_edit);
        layout->setStretch(0, 1);
        layout->setStretch(1, 1);

        ExampleView *view = new ExampleView;
        view->setWidget(widget);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "x"
        );
        frame->setWidget(view);

        connect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateValue(int)));
//        connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(updateValue(int)));

        mainLayout->addWidget(frame);
    }
}

SliderExamples::~SliderExamples()
{
}

void SliderExamples::updateValue(int value)
{
    _edit->setText(QString::number(value));
}
