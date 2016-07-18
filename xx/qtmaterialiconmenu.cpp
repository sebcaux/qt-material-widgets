#include "xx/qtmaterialiconmenu.h"
#include "xx/qtmaterialiconmenu_p.h"
#include <QEvent>
#include <QTimer>
#include "xxlib/qtmaterialoverlaywidget.h"
#include "xx/qtmaterialcollapsiblemenu.h"

/*!
 *  \class QtMaterialIconMenuPrivate
 *  \internal
 */

QtMaterialIconMenuPrivate::QtMaterialIconMenuPrivate(QtMaterialIconMenu *q)
    : QtMaterialIconButtonPrivate(q)
{
}

QtMaterialIconMenuPrivate::~QtMaterialIconMenuPrivate()
{
}

void QtMaterialIconMenuPrivate::init()
{
    Q_Q(QtMaterialIconMenu);

    menuOverlay  = new QtMaterialOverlayWidget(q);
    menu         = new QtMaterialCollapsibleMenu;
    autoCollapse = true;

    menuOverlay->setParent(q->parentWidget());
    menuOverlay->setAttribute(Qt::WA_TransparentForMouseEvents);
    menuOverlay->installEventFilter(q);

    menu->setParent(menuOverlay);
    menu->setMaximumHeight(300);
    menu->setMinimumWidth(200);

    QObject::connect(menu, SIGNAL(aboutToCollapse()), q, SLOT(makeTransparent()));
    QObject::connect(menu, SIGNAL(wasExpanded()), q, SLOT(makeOpaque()));
    QObject::connect(menu, SIGNAL(aboutToExpand()), menuOverlay, SLOT(raise()));
    QObject::connect(menu, SIGNAL(itemClicked(int)), q, SIGNAL(itemSelected(int)));
    QObject::connect(menu, SIGNAL(itemClicked(int)), q, SLOT(collapseDelayed()));
}

/*!
 *  \class QtMaterialIconMenu
 */

QtMaterialIconMenu::QtMaterialIconMenu(const QIcon &icon, QWidget *parent)
    : QtMaterialIconButton(*new QtMaterialIconMenuPrivate(this), parent)
{
    d_func()->init();

    setIcon(icon);
}

QtMaterialIconMenu::~QtMaterialIconMenu()
{
}

void QtMaterialIconMenu::addMenuItem(const QString &text)
{
    Q_D(QtMaterialIconMenu);

    d->menu->addMenuItem(text);
}

void QtMaterialIconMenu::addMenuItem(QtMaterialMenuItem *item)
{
    Q_D(QtMaterialIconMenu);

    d->menu->addMenuItem(item);
}

QtMaterialMenuItem *QtMaterialIconMenu::itemAt(int index) const
{
    Q_D(const QtMaterialIconMenu);

    return d->menu->menuItemAt(index);
}

void QtMaterialIconMenu::setAutoCollapse(bool value)
{
    Q_D(QtMaterialIconMenu);

    d->autoCollapse = value;
}

bool QtMaterialIconMenu::autoCollapse() const
{
    Q_D(const QtMaterialIconMenu);

    return d->autoCollapse;
}

void QtMaterialIconMenu::makeTransparent()
{
    Q_D(QtMaterialIconMenu);

    d->menuOverlay->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void QtMaterialIconMenu::makeOpaque()
{
    Q_D(QtMaterialIconMenu);

    d->menuOverlay->setAttribute(Qt::WA_TransparentForMouseEvents, false);
}

void QtMaterialIconMenu::collapseDelayed()
{
    Q_D(QtMaterialIconMenu);

    if (d->autoCollapse) {
        QTimer::singleShot(200, d->menu, SLOT(collapse()));
    }
}

/*!
 *  \reimp
 */
bool QtMaterialIconMenu::event(QEvent *event)
{
    Q_D(QtMaterialIconMenu);

    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize:
    {
        const QSize sh = d->menu->sizeHint();
        QPoint p = pos();
        p += QPoint(width()/2, height()/2);
        d->menu->setGeometry(p.x(), p.y(), sh.width(), sh.height());
        break;
    }
    case QEvent::MouseButtonRelease:
    {
        if (isEnabled()) {
            d->menu->expand();
        }
        break;
    }
    case QEvent::ParentChange:
    {
        QWidget *widget;
        if ((widget = parentWidget())) {
            d->menuOverlay->setParent(widget);
        }
        break;
    }
    default:
        break;
    }
    return QtMaterialIconButton::event(event);
}

/*!
 *  \reimp
 */
bool QtMaterialIconMenu::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(QtMaterialIconMenu);

    if (QEvent::MouseButtonPress == event->type()) {
        d->menu->collapse();
    }
    return QtMaterialIconButton::eventFilter(obj, event);
}
