#include <QLayout>
#include <QEvent>
#include <QButtonGroup>
#include "radiobuttonexamples.h"
#include "components/radiobutton.h"
#include "exampleview.h"
#include "frame.h"

RadioButtonExamples::RadioButtonExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *layout = widget()->layout();

    {
        QButtonGroup *bg = new QButtonGroup(this);

        RadioButton *radioButton1 = new RadioButton;
        RadioButton *radioButton2 = new RadioButton;
        RadioButton *radioButton3 = new RadioButton;

        radioButton1->setText("Auto select");
        radioButton2->setText("Option #2");

        bg->addButton(radioButton1);
        bg->addButton(radioButton2);
        bg->addButton(radioButton3);

        QWidget *widget = new QWidget;
        QVBoxLayout *vbl = new QVBoxLayout;

        QSizePolicy policy;
        policy.setVerticalPolicy(QSizePolicy::Maximum);
        widget->setSizePolicy(policy);

        widget->setLayout(vbl);
        //widget->setFixedHeight(100);

        vbl->addWidget(radioButton1);
        vbl->addWidget(radioButton2);
        vbl->addWidget(radioButton3);

        ExampleView *view = new ExampleView;
        view->setWidget(widget);

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
