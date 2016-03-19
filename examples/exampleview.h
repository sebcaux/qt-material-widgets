#ifndef EXAMPLEVIEW_H
#define EXAMPLEVIEW_H

#include <QGraphicsView>

class ExampleView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit ExampleView(QWidget *parent = 0);
    ~ExampleView();
};

#endif // EXAMPLEVIEW_H
