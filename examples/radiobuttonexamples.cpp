#include <QLayout>
#include <QEvent>
#include "radiobuttonexamples.h"
#include "components/radiobutton.h"
#include "exampleview.h"
#include "frame.h"

RadioButtonExamples::RadioButtonExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *layout = widget()->layout();

    {
        RadioButton *radioButton = new RadioButton;

        ExampleView *view = new ExampleView;
        view->setWidget(radioButton);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
}

RadioButtonExamples::~RadioButtonExamples()
{
}
