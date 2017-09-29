#include <QLayout>
#include <QCheckBox>
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
        toggle->setOrientation(Qt::Vertical);

        toggle->setDisabled(true);

        ExampleView *view = new ExampleView;
        view->setWidget(toggle);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "Toggle *toggle = new Toggle;\n"
            "toggle->setOrientation(Qt::Vertical);"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        Toggle *toggle = new Toggle;
        toggle->setOrientation(Qt::Vertical);

        toggle->setChecked(true);
        toggle->setDisabled(true);

        ExampleView *view = new ExampleView;
        view->setWidget(toggle);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "Toggle *toggle = new Toggle;\n"
            "toggle->setOrientation(Qt::Vertical);"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        Toggle *toggle = new Toggle;
        toggle->setFixedSize(200, 140);

        ExampleView *view = new ExampleView;
        view->setWidget(toggle);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "Toggle *toggle = new Toggle;\n"
            "toggle->setFixedSize(200, 140);"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        Toggle *toggle = new Toggle;
        //toggle->setFixedSize(200, 50);

        ExampleView *view = new ExampleView;
        view->setWidget(toggle);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
                    ""
        );
        frame->setWidget(view);

        layout->addWidget(frame);

        QCheckBox *cb = new QCheckBox;
        layout->addWidget(cb);

        connect(cb, SIGNAL(toggled(bool)), toggle, SLOT(setChecked(bool)));
    }
    {
        Toggle *toggle = new Toggle;
        toggle->setOrientation(Qt::Vertical);
        toggle->setFixedSize(50, 250);

        ExampleView *view = new ExampleView;
        view->setWidget(toggle);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "Toggle *toggle = new Toggle;\n"
            "toggle->setOrientation(Qt::Vertical);\n"
            "toggle->setFixedSize(50, 250);"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
}

ToggleExamples::~ToggleExamples()
{
}
