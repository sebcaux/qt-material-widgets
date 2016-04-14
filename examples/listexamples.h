#ifndef LISTEXAMPLES_H
#define LISTEXAMPLES_H

#include "examplelist.h"

class ListExamples : public ExampleList
{
    Q_OBJECT

public:
    explicit ListExamples(QWidget *parent = 0);
    ~ListExamples();
};

#endif // LISTEXAMPLES_H
