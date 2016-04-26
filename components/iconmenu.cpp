#include <QEvent>
#include <QLayout>
#include "iconmenu.h"
#include "menu.h"

MenuOverlay::MenuOverlay(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_NoSystemBackground);
}

MenuOverlay::~MenuOverlay()
{
}

IconMenu::IconMenu(const QIcon &icon, QWidget *parent)
    : IconButton(icon, parent),
      _menuOverlay(new MenuOverlay(parent)),
      _menu(new Menu(_menuOverlay)),
      _menuGeometryWidget(0)
{
    setCheckable(true);

    _menu->addMenuItem("Maps");
    _menu->addMenuItem("Books");
    _menu->addMenuItem("Flights");
    _menu->addMenuItem("Apps");
}

IconMenu::~IconMenu()
{
}

void IconMenu::setOverlayParent(QWidget *parent)
{
    _menuOverlay->setParent(parent);
}

bool IconMenu::event(QEvent *event)
{
    if (QEvent::ParentChange == event->type()) {
        setOverlayParent(parentWidget());
        QSize hint = _menu->layout()->sizeHint();
        _menuOverlay->setGeometry(0, 0, hint.width(), hint.height());
    }
    return IconButton::event(event);
}
