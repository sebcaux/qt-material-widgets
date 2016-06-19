#include <QVBoxLayout>
#include <QProgressBar>
#include <QPushButton>
#include "appbarexamples.h"
#include "components/appbar.h"
#include "frame.h"
#include "components/progress.h"
#include "components/circularprogress.h"

AppBarExamples::AppBarExamples(QWidget *parent)
    : QWidget(parent)
{
    Progress *p = new Progress;

    QVBoxLayout *l = new QVBoxLayout;

    setLayout(l);

    l->addStretch(1);

    l->addWidget(p);

    CircularProgress *cp = new CircularProgress;
    cp->setSize(30);

    l->addWidget(cp);

    QProgressBar *pb = new QProgressBar;

    QPushButton *b = new QPushButton;

    l->addWidget(b);

    l->addWidget(pb);

    /*
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
    */
}

AppBarExamples::~AppBarExamples()
{
}
