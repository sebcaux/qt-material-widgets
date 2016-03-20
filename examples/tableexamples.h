#ifndef TABLEEXAMPLES_H
#define TABLEEXAMPLES_H

#include "examplelist.h"

class TableExamples : public ExampleList
{
    Q_OBJECT

public:
    explicit TableExamples(QWidget *parent = 0);
    ~TableExamples();
};

#endif // TABLEEXAMPLES_H
