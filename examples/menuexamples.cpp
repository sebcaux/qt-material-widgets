#include <QLayout>
#include <QEvent>
#include "menuexamples.h"
#include "components/menu.h"
#include "exampleview.h"
#include "frame.h"

MenuExamples::MenuExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *layout = widget()->layout();

    {
        Menu *menu = new Menu;

        ExampleView *view = new ExampleView;
        view->setWidget(menu);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
}

MenuExamples::~MenuExamples()
{
}
