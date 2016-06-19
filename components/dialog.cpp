#include "dialog_p.h"
#include "dialog.h"
#include <QEvent>
#include <QPainter>
#include "dialog_internal.h"

DialogPrivate::DialogPrivate(Dialog *q)
    : q_ptr(q)
{
}

void DialogPrivate::init()
{
    Q_Q(Dialog);

    DialogWindow *window = new DialogWindow(q);
}

Dialog::Dialog(QWidget *parent)
    : QWidget(parent),
      d_ptr(new DialogPrivate(this))
{
}

Dialog::~Dialog()
{
}

bool Dialog::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::ParentChange:
    {
        if (!parent())
            break;

        parent()->installEventFilter(this);

        QWidget *widget;
        if ((widget = parentWidget())) {
            setGeometry(widget->rect());
        }
        break;
    }
    case QEvent::ParentAboutToChange:
    {
        if (!parent())
            break;

        parent()->removeEventFilter(this);
        break;
    }
    default:
        break;
    }
    return QWidget::event(event);
}

bool Dialog::eventFilter(QObject *obj, QEvent *event)
{
    QEvent::Type type = event->type();

    if (QEvent::Move == type || QEvent::Resize == type)
    {
        QWidget *widget;
        if ((widget = parentWidget())) {
            setGeometry(widget->rect());
        }
    }
    return QWidget::eventFilter(obj, event);
}

void Dialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QPen pen;
    pen.setWidth(4);
    painter.setPen(pen);

    painter.drawRect(rect());
}
