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
        RadioButton *radioButton4 = new RadioButton;
        RadioButton *radioButton5 = new RadioButton;

        radioButton3->setCheckedIcon(QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
        radioButton3->setUncheckedIcon(QIcon("../qt-material-widgets/ic_star_border_black_24px.svg"));

        radioButton1->setText("Auto select");
        radioButton2->setText("Option #2");
        radioButton4->setText("Disabled option");
        radioButton5->setText("Disabled option (checked)");

        radioButton4->setDisabled(true);
        radioButton5->setDisabled(true);
        radioButton5->setChecked(true);

        bg->addButton(radioButton1, 1);
        bg->addButton(radioButton2, 2);
        bg->addButton(radioButton3, 3);
        bg->addButton(radioButton4, 4);
        bg->addButton(radioButton5, 5);

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
        vbl->addWidget(radioButton4);
        vbl->addWidget(radioButton5);

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
