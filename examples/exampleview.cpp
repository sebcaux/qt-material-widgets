#include "exampleview.h"

ExampleView::ExampleView(QWidget *parent)
    : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    setScene(scene);
}

ExampleView::~ExampleView()
{
}

