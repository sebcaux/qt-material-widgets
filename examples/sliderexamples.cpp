#include <QVBoxLayout>
#include "sliderexamples.h"
#include "components/slider.h"
#include "exampleview.h"
#include "frame.h"

SliderExamples::SliderExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *mainLayout = widget()->layout();

    {
        Slider *slider = new Slider;

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
        Slider *slider = new Slider;

        ExampleView *view = new ExampleView;
        view->setWidget(slider);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "Slider *slider = new Slider;"
        );
        frame->setWidget(view);

        mainLayout->addWidget(frame);
    }
}

SliderExamples::~SliderExamples()
{
}
