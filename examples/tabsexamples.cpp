#include <QVBoxLayout>
#include <QStackedLayout>
#include <QLabel>
#include "tabsexamples.h"
#include "components/tabs.h"
#include "components/tab.h"
#include "frame.h"

TabsExamples::TabsExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *mainLayout = widget()->layout();

    {
        QWidget *widget = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout;

        widget->setLayout(layout);

        QStackedLayout *stack = new QStackedLayout;
        stack->addWidget(new QLabel("<center>First</center>"));
        stack->addWidget(new QLabel("<center>Second</center>"));
        stack->addWidget(new QLabel("<center>Third</center>"));

        Tabs *tabs = new Tabs;
        layout->addWidget(tabs);
        layout->addLayout(stack);
        layout->setContentsMargins(0, 0, 0, 0);

        tabs->addTab(new Tab("First"));
        tabs->addTab(new Tab("Second"));
        tabs->addTab(new Tab("Third"));

        QScrollArea *area = new QScrollArea;
        area->setWidget(widget);
        area->setWidgetResizable(true);
        area->setBackgroundRole(QPalette::Base);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            "QVBoxLayout *layout = new QVBoxLayout;\n"
            "\n"
            "Tabs *tabs = new Tabs;\n"
            "tabs->addTab(new Tab(\"First\"));\n"
            "tabs->addTab(new Tab(\"Second\"));\n"
            "tabs->addTab(new Tab(\"Third\"));\n"
            "layout->addWidget(tabs);\n"
            "\n"
            "QStackedLayout *stack = new QStackedLayout;\n"
            "stack->addWidget(new QLabel(\"<center>First</center>\"));\n"
            "stack->addWidget(new QLabel(\"<center>Second</center>\"));\n"
            "stack->addWidget(new QLabel(\"<center>Third</center>\"));\n"
            "layout->addLayout(stack);\n"
            "\n"
            "layout->setContentsMargins(0, 0, 0, 0);\n"
            "\n"
            "connect(tabs, SIGNAL(currentChanged(int)), stack, SLOT(setCurrentIndex(int)));\n"
        );
        frame->setWidget(area);

        connect(tabs, SIGNAL(currentChanged(int)), stack, SLOT(setCurrentIndex(int)));

        mainLayout->addWidget(frame);
    }
}

TabsExamples::~TabsExamples()
{
}
