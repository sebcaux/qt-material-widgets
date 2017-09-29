#include "iconmenu.h"
#include <QEvent>
#include <QLayout>
#include <QPropertyAnimation>
#include <QDebug>
#include <QPainter>
#include "menu.h"
#include "xxlib/qtmaterialoverlaywidget.h"
//#include "lib/scaleeffect.h"

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
      _menuOverlay(new QtMaterialOverlayWidget),
      _menu(new Menu(_menuOverlay)),
      _animation(new QPropertyAnimation(this)),
      //_effect(new ScaleEffect(this)),
      _menuVisible(false),
      _progress(1)
{
    setCheckable(true);
    setOverlayParent(parent);

    _animation->setPropertyName("progress");
    _animation->setTargetObject(this);
    _animation->setDuration(340);
    _animation->setStartValue(1);
    _animation->setEndValue(0);

    _animation->setEasingCurve(QEasingCurve::InQuad);

    _menu->hide();

    /*
    _menu->setGraphicsEffect(_effect);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(9);
    effect->setOffset(QPoint(0, 0));
    effect->setColor(QColor(0, 0, 0, 200));
    _menuOverlay->setGraphicsEffect(effect);
    */

    //_menuOverlay->installEventFilter(this);

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

    //_effect->setScale(progress, progress);
    updateOverlayGeometry();

    emit progressChanged(progress);
    update();
}

void IconMenu::setOverlayParent(QWidget *parent)
{
    _menuOverlay->setParent(parent);
}

void IconMenu::toggleMenu()
{
    if (QAbstractAnimation::Running != _animation->state()) {
        _animation->setEasingCurve(_menuVisible
            ? QEasingCurve::OutQuad
            : QEasingCurve::InQuad);
    }

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
    if (QEvent::MouseButtonRelease == event->type() && _menuVisible && _menuOverlay == obj)
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
    const QPoint pos = _menuPos;
    const QSize size = _menu->layout()->sizeHint();
    if (QAbstractAnimation::Running == _animation->state()) {
        _menu->setGeometry(QRect(pos, size*_progress));
    } else {
        _menu->setGeometry(QRect(pos, size));
    }
}
