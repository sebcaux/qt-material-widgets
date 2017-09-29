#include <QLayout>
#include <QEvent>
#include <QCheckBox>
#include "checkboxexamples.h"
#include "components/checkbox.h"
#include "exampleview.h"
#include "frame.h"

CheckboxExamples::CheckboxExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *layout = widget()->layout();

    {
        CheckBox *checkbox = new CheckBox;
        checkbox->setText("Do the macarena");
        checkbox->setDisabled(true);
        checkbox->setChecked(true);

        ExampleView *view = new ExampleView;
        view->setWidget(checkbox);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);


        QCheckBox *cb = new QCheckBox;
        layout->addWidget(cb);

        connect(cb, SIGNAL(toggled(bool)), checkbox, SLOT(setDisabled(bool)));
    }
}

CheckboxExamples::~CheckboxExamples()
{
}
