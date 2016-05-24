#include <QVBoxLayout>
#include <QLabel>
#include "examplelist.h"

ExampleList::ExampleList(QWidget *parent)
    : QScrollArea(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QWidget *widget = new QWidget;

    widget->setLayout(layout);

    //QSizePolicy policy;
    //policy.setHorizontalPolicy(QSizePolicy::Expanding);
    //policy.setVerticalPolicy(QSizePolicy::Maximum);
    //widget->setSizePolicy(policy);

    setWidget(widget);
    setWidgetResizable(true);

    setFrameShape(QFrame::NoFrame);
}

ExampleList::~ExampleList()
{
}
