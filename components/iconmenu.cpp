#include <QEvent>
#include "iconmenu.h"
#include "menu.h"

MenuOverlay::MenuOverlay(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
}

MenuOverlay::~MenuOverlay()
{
}

IconMenu::IconMenu(const QIcon &icon, QWidget *parent)
    : IconButton(icon, parent),
      _overlay(new MenuOverlay(parent)),
      _geometryWidget(0),
      _menu(new Menu)
{
    _menu->setParent(_overlay);

    _menu->addMenuItem("Maps");
    _menu->addMenuItem("Books");
    _menu->addMenuItem("Flights");
    _menu->addMenuItem("Apps");
}

IconMenu::~IconMenu()
{
}

bool IconMenu::event(QEvent *event)
{
    if (QEvent::ParentChange == event->type()) {
        _menu->setParent(parentWidget());
    }
    return IconButton::event(event);
}
