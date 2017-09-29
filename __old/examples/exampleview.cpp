#include <QGridLayout>
#include <QLabel>
#include "exampleview.h"

ExampleView::ExampleView(QWidget *parent)
    : QScrollArea(parent),
      _widget(0),
      _layout(new QGridLayout)
{
    setLayout(_layout);
}

ExampleView::~ExampleView()
{
}

void ExampleView::setWidget(QWidget *widget)
{
    if (widget == _widget)
        return;

    if (_widget) {
        _layout->replaceWidget(_widget, widget);
    } else {
        _layout->addWidget(new QLabel, 1, 0);
        _layout->addWidget(widget, 1, 1);
        _layout->addWidget(new QLabel, 1, 2);
        _layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    }
    _widget = widget;
}
