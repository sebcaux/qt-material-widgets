#include <QLayout>
#include <QPushButton>
#include "flatbuttonexamples.h"
#include "components/flatbutton.h"
#include "exampleview.h"
#include "frame.h"

FlatButtonExamples::FlatButtonExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *layout = widget()->layout();

    {
        FlatButton *flatButton = new FlatButton;
        flatButton->setText("Press me!");
        flatButton->setMinimumSize(200, 42);

//        flatButton->setRole(Material::Primary);
//        flatButton->setDisabled(true);

        ExampleView *view = new ExampleView;
        view->setWidget(flatButton);
        view->setBackgroundRole(QPalette::Base);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "FlatButton *flatButton = new FlatButton;\n"
            "flatButton->setText(\"Press me!\");"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        FlatButton *flatButton = new FlatButton;
        flatButton->setText("Press me!");
        flatButton->setIcon(QIcon("../qt-material-widgets/face.svg"));
        flatButton->setMinimumSize(200, 50);

        ExampleView *view = new ExampleView;
        view->setWidget(flatButton);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "FlatButton *flatButton = new FlatButton;\n"
            "flatButton->setText(\"Press me!\");\n"
            "flatButton->setIcon(QIcon(\"face.svg\"));"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        QPushButton *flatButton = new QPushButton;
        flatButton->setText("Press me!");
        flatButton->setIcon(QIcon("../qt-material-widgets/face.svg"));
        flatButton->setMinimumSize(200, 50);
        flatButton->setCheckable(true);

        ExampleView *view = new ExampleView;
        view->setWidget(flatButton);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
                    ""
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
}

FlatButtonExamples::~FlatButtonExamples()
{
}
