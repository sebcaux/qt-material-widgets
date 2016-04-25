#include <QEvent>
#include <QLayout>
#include "iconmenu.h"
#include "menu.h"

MenuOverlay::MenuOverlay(QWidget *parent)
    : QWidget(parent)
{
    //setAttribute(Qt::WA_TransparentForMouseEvents);
    //setAttribute(Qt::WA_NoSystemBackground);
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
    _menu->addMenuItem("Maps");
    _menu->addMenuItem("Books");
    _menu->addMenuItem("Flights");
    _menu->addMenuItem("Apps");

    setAttribute(Qt::WA_TransparentForMouseEvents);
}

IconMenu::~IconMenu()
{
}

bool IconMenu::event(QEvent *event)
{
    if (QEvent::ParentChange == event->type()) {
        _menuOverlay->setParent(parentWidget());

        QSize hint = _menu->layout()->sizeHint();
        _menuOverlay->setGeometry(0, 0, hint.width(), hint.height());
    }
    return IconButton::event(event);
}
