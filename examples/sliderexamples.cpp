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
        QWidget *widget = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout;

        widget->setLayout(layout);

        Slider *slider = new Slider;

        ExampleView *view = new ExampleView;
        view->setWidget(slider);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "---"
        );
        frame->setWidget(view);

        mainLayout->addWidget(frame);
    }
    {
        QWidget *widget = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout;

        widget->setLayout(layout);

        Slider *slider = new Slider;

        ExampleView *view = new ExampleView;
        view->setWidget(slider);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "---"
        );
        frame->setWidget(view);

        mainLayout->addWidget(frame);
    }
}

SliderExamples::~SliderExamples()
{
}
