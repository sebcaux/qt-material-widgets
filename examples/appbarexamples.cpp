#include <QVBoxLayout>
#include "appbarexamples.h"
#include "components/appbar.h"
#include "frame.h"
#include "components/progress.h"

AppBarExamples::AppBarExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *mainLayout = widget()->layout();

    {
        QWidget *widget = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout;

        widget->setLayout(layout);

        AppBar *appBar = new AppBar;
        layout->addWidget(appBar);
        layout->addStretch();
        layout->setContentsMargins(0, 0, 0, 0);

        QScrollArea *area = new QScrollArea;
        area->setWidget(widget);
        area->setWidgetResizable(true);
        area->setBackgroundRole(QPalette::Base);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "QVBoxLayout *layout = new QVBoxLayout;\n"
            "AppBar *appBar = new AppBar;\n"
            "layout->addWidget(appBar);\n"
            "layout->addStretch();\n"
            "layout->setContentsMargins(0, 0, 0, 0);"
        );
        frame->setWidget(area);

        mainLayout->addWidget(frame);
    }
    {
        QWidget *widget = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout;

        widget->setLayout(layout);

        Progress *p = new Progress;

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            ""
        );
        frame->setWidget(p);

        mainLayout->addWidget(frame);
    }
}

AppBarExamples::~AppBarExamples()
{
}
