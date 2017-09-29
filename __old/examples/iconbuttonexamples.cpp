#include <QLayout>
#include <QEvent>
#include "iconbuttonexamples.h"
#include "components/iconbutton.h"
#include "exampleview.h"
#include "frame.h"

IconButtonExamples::IconButtonExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *layout = widget()->layout();

    {
        IconButton *iconButton = new IconButton(QIcon("../qt-material-widgets/face.svg"), this);

        ExampleView *view = new ExampleView;
        view->setWidget(iconButton);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "IconButton *iconButton = new IconButton(QIcon(\"face.svg\"));\n"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        IconButton *iconButton = new IconButton(QIcon("../qt-material-widgets/face.svg"));
        iconButton->setIconSize(QSize(64, 64));

        ExampleView *view = new ExampleView;
        view->setWidget(iconButton);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "IconButton *iconButton = new IconButton(QIcon(\"face.svg\"));\n"
            "iconButton->setIconSize(QSize(64, 64));\n"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        IconButton *iconButton = new IconButton(QIcon("../qt-material-widgets/face.svg"));
        iconButton->setIconSize(QSize(128, 128));

        iconButton->setDisabled(true);

        ExampleView *view = new ExampleView;
        view->setWidget(iconButton);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "IconButton *iconButton = new IconButton(QIcon(\"face.svg\"));\n"
            "iconButton->setIconSize(QSize(128, 128));\n"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
}

IconButtonExamples::~IconButtonExamples()
{
}
