#include <QEvent>
#include <QDebug>
#include "exampleview.h"

ExampleView::ExampleView(QWidget *parent)
    : QScrollArea(parent),
      _widget(0)
{
}

ExampleView::~ExampleView()
{
}

void ExampleView::setWidget(QWidget *widget)
{
    if (_widget)
        _widget->removeEventFilter(this);

    widget->setParent(this);
    widget->installEventFilter(this);
    _widget = widget;
}

bool ExampleView::eventFilter(QObject *obj, QEvent *event)
{
    QEvent::Type type = event->type();
    if (QEvent::Resize == type || QEvent::Move == type) {
        QRect r(_widget->geometry());
        qDebug() << r;
        r.moveCenter(rect().center());
        _widget->setGeometry(r);
    }
    return QScrollArea::eventFilter(obj, event);
}
