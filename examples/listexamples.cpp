#include <QLayout>
#include <QEvent>
#include "listexamples.h"
#include "components/list.h"
#include "exampleview.h"
#include "frame.h"

ListExamples::ListExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *layout = widget()->layout();

    {
        List *list = new List;

        ExampleView *view = new ExampleView;
        view->setWidget(list);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
}

ListExamples::~ListExamples()
{
}
