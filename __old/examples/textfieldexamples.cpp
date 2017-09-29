#include <QLayout>
#include <QEvent>
#include <QLineEdit>
#include "textfieldexamples.h"
#include "components/textfield.h"
#include "exampleview.h"
#include "frame.h"

TextFieldExamples::TextFieldExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *layout = widget()->layout();

    {
        TextField *textField = new TextField;
        textField->setPlaceholderText("This is a placeholder");
        textField->setLabel("Enter your name");

        ExampleView *view = new ExampleView;
        view->setWidget(textField);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        TextField *textField = new TextField;
        textField->setLabel("Enter your name");

        ExampleView *view = new ExampleView;
        view->setWidget(textField);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        TextField *textField = new TextField;
        textField->setPlaceholderText("No label, only placeholder");

        ExampleView *view = new ExampleView;
        view->setWidget(textField);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        TextField *textField = new TextField;

        ExampleView *view = new ExampleView;
        view->setWidget(textField);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        TextField *textField = new TextField;
        textField->setDisabled(true);
        textField->setLabel("Disabled");

        ExampleView *view = new ExampleView;
        view->setWidget(textField);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        QLineEdit *edit = new QLineEdit;

        ExampleView *view = new ExampleView;
        view->setWidget(edit);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
}

TextFieldExamples::~TextFieldExamples()
{
}
