#include <QLayout>
#include "raisedbuttonexamples.h"
#include "components/raisedbutton.h"
#include "exampleview.h"
#include "frame.h"

RaisedButtonExamples::RaisedButtonExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *layout = widget()->layout();

    {
        RaisedButton *raisedButton = new RaisedButton;
        raisedButton->setText("Press me!");
        raisedButton->setMinimumSize(200, 42);

        ExampleView *view = new ExampleView;
        view->setWidget(raisedButton);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "RaisedButton *raisedButton = new RaisedButton;\n"
            "raisedButton->setText(\"Press me!\");"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
}

RaisedButtonExamples::~RaisedButtonExamples()
{
}
