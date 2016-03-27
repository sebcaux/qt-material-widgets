#include <QLayout>
#include "toggleexamples.h"
#include "components/toggle.h"
#include "exampleview.h"
#include "frame.h"

ToggleExamples::ToggleExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *layout = widget()->layout();

    {
        Toggle *toggle = new Toggle;

        ExampleView *view = new ExampleView;
        view->setWidget(toggle);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "Toggle *toggle = new Toggle;"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        Toggle *toggle = new Toggle;
        toggle->setFixedSize(250, 180);

        ExampleView *view = new ExampleView;
        view->setWidget(toggle);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "Toggle *toggle = new Toggle;\n"
            "toggle->setFixedSize(250, 180);"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
}

ToggleExamples::~ToggleExamples()
{
}

