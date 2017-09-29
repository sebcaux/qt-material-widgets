#ifndef TOGGLEEXAMPLES_H
#define TOGGLEEXAMPLES_H

#include "examplelist.h"

class ToggleExamples : public ExampleList
{
    Q_OBJECT

public:
    explicit ToggleExamples(QWidget *parent = 0);
    ~ToggleExamples();
};

#endif // TOGGLEEXAMPLES_H
