#ifndef MENUEXAMPLES_H
#define MENUEXAMPLES_H

#include "examplelist.h"

class MenuExamples : public ExampleList
{
    Q_OBJECT

public:
    explicit MenuExamples(QWidget *parent = 0);
    ~MenuExamples();
};

#endif // MENUEXAMPLES_H
