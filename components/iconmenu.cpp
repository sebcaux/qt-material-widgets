#include <QEvent>
#include <QLayout>
#include <QPropertyAnimation>
#include <QDebug>
#include <QPainter>
#include "iconmenu.h"
#include "menu.h"
#include "lib/scaleeffect.h"

MenuOverlay::MenuOverlay(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

MenuOverlay::~MenuOverlay()
{
}

IconMenu::IconMenu(const QIcon &icon, QWidget *parent)
    : IconButton(icon, parent),
      _menuOverlay(new MenuOverlay),
      _menu(new Menu(_menuOverlay)),
      _animation(new QPropertyAnimation(this)),
      _effect(new ScaleEffect(this)),
      _menuVisible(false),
      _progress(1)
{
    setCheckable(true);
    setOverlayParent(parent);

    _animation->setPropertyName("progress");
    _animation->setTargetObject(this);
    _animation->setDuration(200);
    _animation->setStartValue(1);
    _animation->setEndValue(0);

    _animation->setEasingCurve(QEasingCurve::InOutCubic);

    _menu->hide();
    _menu->setGraphicsEffect(_effect);

    _menuOverlay->installEventFilter(this);

    connect(this, SIGNAL(clicked(bool)), this, SLOT(toggleMenu()));
    connect(_animation, SIGNAL(finished()), this, SLOT(animationFinished()));

    _menu->addMenuItem("Maps");
    _menu->addMenuItem("Books");
    _menu->addMenuItem("Flights");
    _menu->addMenuItem("Apps");
}

IconMenu::~IconMenu()
{
}

void IconMenu::setProgress(qreal progress)
{
    if (_progress == progress)
        return;
    _progress = progress;

    _effect->setScale(0.5*(1 + progress), progress);

    emit progressChanged(progress);
    update();
}

void IconMenu::setOverlayParent(QWidget *parent)
{
    _menuOverlay->setParent(parent);
}

void IconMenu::toggleMenu()
{
    _animation->setDirection(_menuVisible
        ? QAbstractAnimation::Forward
        : QAbstractAnimation::Backward);
    _animation->start();

    _menuVisible = !_menuVisible;

    if (_menuVisible) {
        _menu->show();
        _menuOverlay->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
}

void IconMenu::animationFinished()
{
    if (!_menuVisible) {
        _menu->hide();
        _menuOverlay->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    }
}

bool IconMenu::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::MouseButtonRelease == event->type() && _menuOverlay == obj)
        toggleMenu();
    return IconButton::eventFilter(obj, event);
}

bool IconMenu::event(QEvent *event)
{
    const QEvent::Type &type = event->type();
    if (QEvent::ParentChange == type) {
        setOverlayParent(parentWidget());
        updateOverlayGeometry();
    } else if (QEvent::Move == type || QEvent::Resize == type) {
        _menuPos = parentWidget()->mapToParent(pos());
        updateOverlayGeometry();
    }
    return IconButton::event(event);
}

void IconMenu::updateOverlayGeometry()
{
    _menu->setGeometry(QRect(_menuPos, _menu->layout()->sizeHint()));
}
