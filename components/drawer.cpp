#include "drawer.h"
#include "drawer_p.h"
#include <QPainter>
#include <QEvent>
#include <QApplication>
#include <QLayout>
#include <QLinearGradient>
#include <QVBoxLayout>
#include "drawer_internal.h"

DrawerPrivate::DrawerPrivate(Drawer *q)
    : q_ptr(q),
      stateMachine(new DrawerStateMachine(q)),
      window(new QWidget),
      width(250)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(window);

    q->setLayout(layout);
    q->setFixedWidth(width+16);

    stateMachine->start();

    QCoreApplication::processEvents();
}

Drawer::Drawer(QWidget *parent)
    : OverlayWidget(parent),
      d_ptr(new DrawerPrivate(this))
{
}

Drawer::~Drawer()
{
}

void Drawer::setDrawerWidth(int width)
{
    Q_D(Drawer);

    d->width = width;
    d->stateMachine->updatePropertyAssignments();
    setFixedWidth(width+16);
}

int Drawer::drawerWidth() const
{
    Q_D(const Drawer);

    return d->width;
}

void Drawer::setDrawerLayout(QLayout *layout)
{
    Q_D(Drawer);

    d->window->setLayout(layout);
}

QLayout *Drawer::drawerLayout() const
{
    Q_D(const Drawer);

    return d->window->layout();
}

void Drawer::openDrawer()
{
    Q_D(Drawer);

    emit d->stateMachine->enterOpenedState();
}

void Drawer::closeDrawer()
{
    Q_D(Drawer);

    emit d->stateMachine->enterClosedState();
}

bool Drawer::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Move == type || QEvent::Resize == type) {
        QLayout *t = layout();
        if (t && 16 != t->contentsMargins().right()) {
            t->setContentsMargins(0, 0, 16, 0);
        }
    }
    return OverlayWidget::eventFilter(obj, event);
}

void Drawer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    painter.drawRect(rect().adjusted(0, 0, -16, 0));

    QLinearGradient gradient(QPointF(width()-16, 0), QPointF(width(), 0));
    gradient.setColorAt(0, QColor(0, 0, 0, 80));
    gradient.setColorAt(0.5, QColor(0, 0, 0, 20));
    gradient.setColorAt(1, QColor(0, 0, 0, 0));
    painter.setBrush(QBrush(gradient));

    painter.drawRect(width()-16, 0, 16, height());
}

QRect Drawer::overlayGeometry() const
{
    Q_D(const Drawer);

    return OverlayWidget::overlayGeometry().translated(d->stateMachine->offset(), 0);
}
