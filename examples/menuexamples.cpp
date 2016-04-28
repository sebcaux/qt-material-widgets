#include <QLayout>
#include <QEvent>
#include "menuexamples.h"
#include "components/menu.h"
#include "exampleview.h"
#include "frame.h"

MenuExamples::MenuExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *layout = widget()->layout();

    {
        Menu *menu = new Menu;

        menu->addMenuItem(tr("Maps"));
        menu->addMenuItem(tr("Books"));
        menu->addMenuItem(tr("Flights"));
        menu->addMenuItem(tr("Apps"));

        ExampleView *view = new ExampleView;
        view->setWidget(menu);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "Menu *menu = new Menu;\n"
            "\n"
            "menu->addMenuItem(tr(\"Maps\"));\n"
            "menu->addMenuItem(tr(\"Books\"));\n"
            "menu->addMenuItem(tr(\"Flights\"));\n"
            "menu->addMenuItem(tr(\"Apps\"));\n"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
}

MenuExamples::~MenuExamples()
{
}
