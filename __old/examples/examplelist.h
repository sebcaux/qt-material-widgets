#ifndef EXAMPLELIST_H
#define EXAMPLELIST_H

#include <QScrollArea>

class ExampleList : public QScrollArea
{
    Q_OBJECT

public:
    explicit ExampleList(QWidget *parent = 0);
    ~ExampleList();
};

#endif // EXAMPLELIST_H
