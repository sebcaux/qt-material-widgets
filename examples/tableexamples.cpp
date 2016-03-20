#include <QVBoxLayout>
#include "tableexamples.h"
#include "components/table.h"
#include "frame.h"

TableExamples::TableExamples(QWidget *parent)
    : ExampleList(parent)
{
    QLayout *mainLayout = widget()->layout();

    {
        Table *table = new Table;

        table->setRowCount(70);
        table->setColumnCount(5);

        Frame *frame = new Frame;
        frame->setCodeSnippet(
            ""
        );
        frame->setWidget(table);

        mainLayout->addWidget(frame);
    }
}

TableExamples::~TableExamples()
{
}
