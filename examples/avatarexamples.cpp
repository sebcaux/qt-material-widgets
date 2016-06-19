#include <QLayout>
#include <QEvent>
#include <QIcon>
#include "avatarexamples.h"
#include "components/avatar.h"
#include "components/badge.h"
#include "exampleview.h"
#include "frame.h"
#include "components/scrollwidget.h"

AvatarExamples::AvatarExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *layout = widget()->layout();

    ScrollBar *sb = new ScrollBar;
    setVerticalScrollBar(sb);

    {
        Avatar *avatar = new Avatar;

        avatar->setLetter(QChar('M'));

        ExampleView *view = new ExampleView;
        view->setWidget(avatar);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        Avatar *avatar = new Avatar;
        Badge *badge = new Badge;
        badge->setText("5");
        badge->setRelativePosition(13, 13);

        avatar->setLetter(QChar('M'));

        ExampleView *view = new ExampleView;
        view->setWidget(avatar);

        //view->setWidget(badge);
        badge->setParent(avatar);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        Avatar *avatar = new Avatar;

        QIcon icon("../qt-material-widgets/ic_message_white_24px.svg");
        avatar->setIcon(icon);

        ExampleView *view = new ExampleView;
        view->setWidget(avatar);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        Avatar *avatar = new Avatar;

        QImage img("../qt-material-widgets/uxceo-128.jpg");
        avatar->setImage(img);

        ExampleView *view = new ExampleView;
        view->setWidget(avatar);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        Avatar *avatar = new Avatar;
        avatar->setSize(80);

        avatar->setLetter(QChar('M'));

        ExampleView *view = new ExampleView;
        view->setWidget(avatar);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        Avatar *avatar = new Avatar;
        avatar->setSize(60);

        QIcon icon("../qt-material-widgets/ic_message_white_24px.svg");
        avatar->setIcon(icon);

        ExampleView *view = new ExampleView;
        view->setWidget(avatar);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        Avatar *avatar = new Avatar;
        avatar->setSize(80);

        QImage img("../qt-material-widgets/uxceo-128.jpg");
        avatar->setImage(img);

        ExampleView *view = new ExampleView;
        view->setWidget(avatar);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
    {
        Avatar *avatar = new Avatar;
        avatar->setSize(80);

        QImage img("../qt-material-widgets/sikh.jpg");
        avatar->setImage(img);

        ExampleView *view = new ExampleView;
        view->setWidget(avatar);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
}

AvatarExamples::~AvatarExamples()
{
}
