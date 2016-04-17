#include <QLayout>
#include <QEvent>
#include "checkboxexamples.h"
#include "components/checkbox.h"
#include "exampleview.h"
#include "frame.h"

CheckboxExamples::CheckboxExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *layout = widget()->layout();

    {
        Checkbox *checkbox = new Checkbox;

        ExampleView *view = new ExampleView;
        view->setWidget(checkbox);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
}

CheckboxExamples::~CheckboxExamples()
{
}
