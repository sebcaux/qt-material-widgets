#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include "sliderexamples.h"
#include "components/slider.h"
#include "exampleview.h"
#include "frame.h"

SliderExamples::SliderExamples(QWidget *parent)
    : ExampleList(parent),
      _edit(new QLineEdit),
      _edit2(new QLineEdit),
      _slider(new Slider),
      _slider2(new Slider)
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

        mainLayout->addWidget(frame);
    }
    {
        QVBoxLayout *layout = new QVBoxLayout;
        QWidget *widget = new QWidget;
        widget->setLayout(layout);
        widget->setMinimumWidth(350);

        QPushButton *button = new QPushButton("Change orientation");

        _slider->setMinimumWidth(250);
        layout->addWidget(_slider);
        layout->addWidget(button);

        ExampleView *view = new ExampleView;
        view->setWidget(widget);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "Slider *slider = new Slider;"
        );
        frame->setWidget(view);

        mainLayout->addWidget(frame);

        connect(button, SIGNAL(pressed()), this, SLOT(flip()));
    }
    {
        QVBoxLayout *layout = new QVBoxLayout;
        QWidget *widget = new QWidget;
        widget->setLayout(layout);
        widget->setMinimumWidth(350);

        QHBoxLayout *hLayout = new QHBoxLayout;
        QPushButton *button = new QPushButton("Update value");
        hLayout->addWidget(_edit2);
        hLayout->addWidget(button);

        _slider2->setMinimumWidth(250);
        layout->addWidget(_slider2);
        layout->addLayout(hLayout);

        ExampleView *view = new ExampleView;
        view->setWidget(widget);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "Slider *slider = new Slider;"
        );
        frame->setWidget(view);

        mainLayout->addWidget(frame);

        connect(button, SIGNAL(pressed()), this, SLOT(updateSliderValue()));

        _slider2->setTracking(false);
    }
}

SliderExamples::~SliderExamples()
{
}

void SliderExamples::updateValue(int value)
{
    _edit->setText(QString::number(value));
}

void SliderExamples::flip()
{
    _slider->setOrientation(Qt::Horizontal == _slider->orientation() ?
        Qt::Vertical : Qt::Horizontal);
}

void SliderExamples::updateSliderValue()
{
    _slider2->setValue(_edit2->text().toInt());
}
