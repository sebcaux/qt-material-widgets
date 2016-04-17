#include <QLayout>
#include <QEvent>
#include "avatarexamples.h"
#include "components/avatar.h"
#include "exampleview.h"
#include "frame.h"

AvatarExamples::AvatarExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *layout = widget()->layout();

    {
        Avatar *avatar = new Avatar;

        ExampleView *view = new ExampleView;
        view->setWidget(avatar);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "hello"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    } }

AvatarExamples::~AvatarExamples()
{
}
