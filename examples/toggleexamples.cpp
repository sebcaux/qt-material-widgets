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
            "??"
        );
        frame->setWidget(view);

        layout->addWidget(frame);

        toggle->update();
    }
}

ToggleExamples::~ToggleExamples()
{
}

