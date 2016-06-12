#include <QLayout>
#include <QPushButton>
#include <QDebug>
#include <QApplication>
#include "flatbuttonexamples.h"
#include "lib/style.h"
#include "components/flatbutton.h"
#include "components/fab.h"
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

        flatButton->setRole(Material::Primary);
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
        flatButton->setMinimumSize(200, 42);

        flatButton->setRole(Material::Secondary);
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
        flatButton->setMinimumSize(200, 42);

        flatButton->setRole(Material::Secondary);
        flatButton->setBackgroundColor(QColor(0, 0, 0, 80));
        //flatButton->setTextColor(Style::instance().themeColor("primary1"));
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
        flatButton->setMinimumSize(200, 42);

        flatButton->setRole(Material::Primary);
        flatButton->setBackgroundMode(Qt::OpaqueMode);
        //flatButton->setPrimaryTextColor(Qt::white);
        flatButton->setPeakOpacity(0.25);

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
        flatButton->setMinimumSize(200, 42);

        flatButton->setRole(Material::Secondary);
        flatButton->setBackgroundMode(Qt::OpaqueMode);
        flatButton->setPeakOpacity(0.25);

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
        flatButton->setMinimumSize(200, 42);

        //flatButton->setRole(Material::Secondary);
        flatButton->setBackgroundMode(Qt::OpaqueMode);
        flatButton->setBackgroundColor(Qt::green);
        flatButton->setPeakOpacity(0.25);

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
        FlatButton *flatButton = new FlatButton;
        flatButton->setText("Press me!");
        flatButton->setDisabled(true);

        ExampleView *view = new ExampleView;
        view->setWidget(flatButton);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
                    ""
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
        //QPushButton *flatButton = new QPushButton;
        //flatButton->setText("Press me!");
        //flatButton->setIcon(QIcon("../qt-material-widgets/face.svg"));
        //flatButton->setMinimumSize(200, 50);
        //flatButton->setCheckable(true);

        //FloatingActionButton *button = new FloatingActionButton(QIcon("../qt-material-widgets/ic_local_dining_white_24px.svg"));

        //qDebug() << QGuiApplication::allWindows();

        //ExampleView *view = new ExampleView;
        //view->setWidget(button);

        //Frame *frame = new Frame;
        //frame->setCodeSnippet(
        //            ""
        //);
        //frame->setWidget(view);

        //layout->addWidget(frame);
}

FlatButtonExamples::~FlatButtonExamples()
{
}
