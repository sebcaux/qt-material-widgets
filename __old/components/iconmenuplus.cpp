#include "iconmenuplus.h"
#include <QEvent>
#include <QPainter>
#include <QLayout>
#include "xxlib/qtmaterialoverlaywidget.h"
//#include "menuplus.h"
#include "xx/qtmaterialcollapsiblemenu.h"
#include "xx/qtmaterialmenuitem.h"
#include <QDebug>

IconMenuPlus::IconMenuPlus(const QIcon &icon, QWidget *parent)
    : QtMaterialIconButton(icon, parent)
{
    menuOverlay = new QtMaterialOverlayWidget;
    menuOverlay->setParent(parentWidget());
    menuOverlay->setAttribute(Qt::WA_TransparentForMouseEvents);

    menu = new QtMaterialCollapsibleMenu;
    menu->setParent(menuOverlay);
    menu->setMaximumHeight(300);

    connect(menu, SIGNAL(aboutToCollapse()), this, SLOT(xxx()));
    connect(menu, SIGNAL(wasExpanded()), this, SLOT(yyy()));

    menuOverlay->installEventFilter(this);
}

IconMenuPlus::~IconMenuPlus()
{
}

void IconMenuPlus::addMenuItem(const QString &text)
{
    menu->addMenuItem(text);
}

void IconMenuPlus::addMenuItem(QtMaterialMenuItem *item)
{
    menu->addMenuItem(item);
}

void IconMenuPlus::xxx()
{
    menuOverlay->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void IconMenuPlus::yyy()
{
    menuOverlay->setAttribute(Qt::WA_TransparentForMouseEvents, false);
}

bool IconMenuPlus::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize:
    {
        const QSize sh = menu->sizeHint();
        QPoint p = pos();
        p += QPoint(width()/2, height()/2);
        menu->setGeometry(p.x(), p.y(), sh.width(), sh.height());
        break;
    }
    case QEvent::MouseButtonRelease:
    {
        menu->expand();
        break;
    }
    case QEvent::ParentChange:
    {
        QWidget *widget;
        if ((widget = parentWidget())) {
            menuOverlay->setParent(widget);
        }
        break;
    }
    default:
        break;
    }
    return QtMaterialIconButton::event(event);
}

bool IconMenuPlus::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::MouseButtonPress == event->type()) {
        menu->collapse();
    }
    return QtMaterialIconButton::eventFilter(obj, event);
}
