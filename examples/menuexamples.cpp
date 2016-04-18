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

        menu->addMenuItem("Maps");
        menu->addMenuItem("Books");
        menu->addMenuItem("Flights");
        menu->addMenuItem("Apps");

        ExampleView *view = new ExampleView;
        view->setWidget(menu);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "Menu *menu = new Menu;\n"
            "\n"
            "menu->addMenuItem(\"Maps\");\n"
            "menu->addMenuItem(\"Books\");\n"
            "menu->addMenuItem(\"Flights\");\n"
            "menu->addMenuItem(\"Apps\");\n"
        );
        frame->setWidget(view);

        layout->addWidget(frame);
    }
}

MenuExamples::~MenuExamples()
{
}
