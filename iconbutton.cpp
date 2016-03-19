#include <QStylePainter>
#include <QStyleOptionButton>
#include <QApplication>
#include <QEvent>
#include <QDebug>
#include "iconbutton.h"
#include "rippleoverlay.h"

IconButton::IconButton(const QIcon &icon, QWidget *parent)
    : QAbstractButton(parent),
      _overlay(new RippleOverlay(parent))
{
    setIcon(icon);

    QSizePolicy policy;
    policy.setWidthForHeight(true);
    setSizePolicy(policy);
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

void IconButton::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event)

    updateOverlayGeometry();
}

void IconButton::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

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

    const QRect &size = geometry();
    _overlay->addRipple(QPoint(size.width(), size.height()), iconSize().width());

    emit clicked();
}

bool IconButton::event(QEvent *event)
{
    if (QEvent::ParentChange == event->type()) {
        _overlay->setParent(parentWidget());
    }
    return QAbstractButton::event(event);
}

void IconButton::updateOverlayGeometry()
{
    if (!_overlay)
        return;

    int x, y, w, h;
    geometry().getRect(&x, &y, &w, &h);
    _overlay->setGeometry(x-w/2, y-h/2, w*2, h*2);
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
