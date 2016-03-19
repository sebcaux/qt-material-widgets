#include <QStylePainter>
#include <QStyleOptionButton>
#include <QApplication>
#include <QEvent>
#include <QDebug>
#include "iconbutton.h"
#include "../lib/rippleoverlay.h"

IconButton::IconButton(const QIcon &icon, QWidget *parent)
    : QAbstractButton(parent),
      _overlay(new RippleOverlay(parent)),
      _geometryWidget(0)
{
    setIcon(icon);

    QSizePolicy policy;
    policy.setWidthForHeight(true);
    setSizePolicy(policy);

    setGeometryWidget(this);
}

IconButton::~IconButton()
{
}

QSize IconButton::sizeHint() const
{
    QStyleOptionButton option(getStyleOption());

    int w = option.iconSize.width() + 4;
    int h = option.iconSize.height();

    return (style()->sizeFromContents(QStyle::CT_PushButton, &option, QSize(w, h), this).
            expandedTo(QApplication::globalStrut()));
}

void IconButton::setGeometryWidget(QWidget *widget)
{
    if (_geometryWidget) {
        _geometryWidget->removeEventFilter(this);
    }
    _geometryWidget = widget;
    widget->installEventFilter(this);
    updateOverlayGeometry();
}

void IconButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStylePainter painter(this);
    QStyleOptionButton option(getStyleOption());
    painter.drawControl(QStyle::CE_PushButton, option);
}

void IconButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if (!_overlay)
        return;

    QPoint p(_overlay->width(), _overlay->height());
    _overlay->addRipple(p/2, iconSize().width());

    emit clicked();
}

bool IconButton::event(QEvent *event)
{
    if (QEvent::ParentChange == event->type() && parentWidget()) {
        _overlay->setParent(parentWidget());
    }
    return QAbstractButton::event(event);
}

bool IconButton::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();
    if (QEvent::Resize == type || QEvent::Move == type) {
        updateOverlayGeometry();
    }
    return QAbstractButton::eventFilter(obj, event);
}

void IconButton::updateOverlayGeometry()
{
    if (!_overlay || !_geometryWidget)
        return;

    const int s = iconSize().width()/2;
    _overlay->setGeometry(_geometryWidget->geometry().adjusted(-s, -s, s, s));
}

QStyleOptionButton IconButton::getStyleOption() const
{
    QStyleOptionButton option;
    option.initFrom(this);
    option.features = QStyleOptionButton::Flat;
    if (isChecked())
        option.state |= QStyle::State_On;
    option.icon = icon();
    option.iconSize = iconSize();
    return option;
}
