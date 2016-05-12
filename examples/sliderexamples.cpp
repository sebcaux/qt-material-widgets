#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include "sliderexamples.h"
#include "components/slider.h"
#include "exampleview.h"
#include "frame.h"

SliderExamples::SliderExamples(QWidget *parent)
    : ExampleList(parent),
      _edit(new QLineEdit),
      _edit2(new QLineEdit),
      _slider(new Slider),
      _slider2(new Slider),
      _slider3(new Slider),
      __slider(new QSlider)
{
    QLayout *mainLayout = widget()->layout();

    {
        QHBoxLayout *layout = new QHBoxLayout;
        QWidget *widget = new QWidget;

        widget->setLayout(layout);

        _slider3->setMinimumWidth(250);

        QCheckBox *checkbox = new QCheckBox;
        QCheckBox *checkbox2 = new QCheckBox;
        QCheckBox *checkbox3 = new QCheckBox;

        layout->addWidget(_slider3);
        layout->addWidget(checkbox);
        layout->addWidget(checkbox2);
        layout->addWidget(checkbox3);

        ExampleView *view = new ExampleView;
        view->setWidget(widget);
        view->setBackgroundRole(QPalette::Base);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "Slider *slider = new Slider;"
        );
        frame->setWidget(view);

        mainLayout->addWidget(frame);

        connect(checkbox, SIGNAL(toggled(bool)), this, SLOT(inv()));
        connect(checkbox2, SIGNAL(toggled(bool)), this, SLOT(togglePageStepMode()));
        connect(checkbox3, SIGNAL(toggled(bool)), this, SLOT(toggleEnabled()));
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

        //_slider->setMinimumWidth(250);
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

        QPushButton *button = new QPushButton("Change orientation");

        //__slider->setMinimumWidth(250);
        layout->addWidget(__slider);
        layout->addWidget(button);

        ExampleView *view = new ExampleView;
        view->setWidget(widget);

        Frame *frame = new Frame;
        frame->setCodeSnippet("xxx");
        frame->setWidget(view);

        mainLayout->addWidget(frame);

        connect(button, SIGNAL(pressed()), this, SLOT(flip2()));
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

        layout->addWidget(new QSlider(Qt::Horizontal));

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
    {
        Slider *slider = new Slider;
        slider->setValue(20);
        slider->setDisabled(true);
        slider->setMinimumWidth(250);

        ExampleView *view = new ExampleView;
        view->setWidget(slider);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "Slider *slider = new Slider;\n"
            "slider->setDisabled(true);\n"
        );
        frame->setWidget(view);

        mainLayout->addWidget(frame);
    }
    {
        QVBoxLayout *layout = new QVBoxLayout;
        QWidget *widget = new QWidget;
        widget->setLayout(layout);
        widget->setMinimumWidth(350);

        Slider *slider;
        QHBoxLayout *hLayout;

        slider = new Slider;

        hLayout = new QHBoxLayout;
        hLayout->addWidget(new QLabel("R"));
        hLayout->addWidget(slider);
        hLayout->addWidget(new QLineEdit);

        layout->addLayout(hLayout);

        slider = new Slider;

        hLayout = new QHBoxLayout;
        hLayout->addWidget(new QLabel("G"));
        hLayout->addWidget(slider);
        hLayout->addWidget(new QLineEdit);

        layout->addLayout(hLayout);

        slider = new Slider;

        hLayout = new QHBoxLayout;
        hLayout->addWidget(new QLabel("B"));
        hLayout->addWidget(slider);
        hLayout->addWidget(new QLineEdit);

        layout->addLayout(hLayout);

        ExampleView *view = new ExampleView;
        view->setWidget(widget);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "xx"
        );
        frame->setWidget(view);

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

void SliderExamples::flip()
{
    _slider->setOrientation(Qt::Horizontal == _slider->orientation() ?
        Qt::Vertical : Qt::Horizontal);
}

void SliderExamples::flip2()
{
    __slider->setOrientation(Qt::Horizontal == __slider->orientation() ?
        Qt::Vertical : Qt::Horizontal);
}

void SliderExamples::updateSliderValue()
{
    _slider2->setValue(_edit2->text().toInt());
}

void SliderExamples::inv()
{
    _slider3->setInvertedAppearance(!_slider3->invertedAppearance());
}

void SliderExamples::togglePageStepMode()
{
    _slider3->setPageStepMode(!_slider3->pageStepMode());
}

void SliderExamples::toggleEnabled()
{
    bool enabled = !_slider3->isEnabled();
    _slider3->setEnabled(enabled);
}
