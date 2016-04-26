#include <QLayout>
#include <QEvent>
#include <QIcon>
#include "iconmenuexamples.h"
#include "components/iconmenu.h"
#include "exampleview.h"
#include "frame.h"

IconMenuExamples::IconMenuExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *layout = widget()->layout();

    {
        IconMenu *iconMenu = new IconMenu(QIcon("../qt-material-widgets/face.svg"));

        ExampleView *view = new ExampleView;
        view->setWidget(iconMenu);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "yyy\n"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
        iconMenu->setOverlayParent(frame);
    }
}

IconMenuExamples::~IconMenuExamples()
{
}
