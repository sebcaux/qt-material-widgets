#include "lib/overlaywidget.h"
#include <QEvent>

OverlayWidget::OverlayWidget(QWidget *parent)
    : QWidget(parent)
{
}

OverlayWidget::~OverlayWidget()
{
}

bool OverlayWidget::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::ParentChange:
    {
        if (!parent()) {
            break;
        }
        parent()->installEventFilter(this);
        setGeometry(overlayGeometry());
        break;
    }
    case QEvent::ParentAboutToChange:
    {
        if (!parent()) {
            break;
        }
        parent()->removeEventFilter(this);
        break;
    }
    default:
        break;
    }
    return QWidget::event(event);
}

bool OverlayWidget::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Move == type || QEvent::Resize == type) {
        setGeometry(overlayGeometry());
    }
    return QWidget::eventFilter(obj, event);
}

QRect OverlayWidget::overlayGeometry() const
{
    QWidget *widget = parentWidget();
    if (widget) {
        return widget->rect();
    }
    return QRect();
}
