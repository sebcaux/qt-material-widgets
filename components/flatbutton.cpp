#include <QDebug>
#include <QStylePainter>
#include <QMouseEvent>
#include <QApplication>
#include "flatbutton.h"

FlatButton::FlatButton(QWidget *parent)
    : QAbstractButton(parent),
      _overlay(new RippleOverlay(this))
{
}

FlatButton::FlatButton(const QString &text, QWidget *parent)
    : QAbstractButton(parent),
      _overlay(new RippleOverlay(this))
{
    setText(text);
}

FlatButton::~FlatButton()
{
}

QSize FlatButton::sizeHint() const
{
    // Mostly lifted from QPushButton

    ensurePolished();

    int w = 0,
        h = 0;

    QStyleOptionButton option(getStyleOption());

#ifndef QT_NO_ICON
    if (!icon().isNull()) {
        int ih = option.iconSize.height();
        int iw = option.iconSize.width() + 4;
        w += iw;
        h = qMax(h, ih);
    }
#endif

    QString s(text());
    bool empty = s.isEmpty();
    if (empty)
        s = QString::fromLatin1("XXXX");
    QFontMetrics fm = fontMetrics();
    QSize sz = fm.size(Qt::TextShowMnemonic, s);
    if (!empty || !w)
        w += sz.width();
    if (!empty || !h)
        h = qMax(h, sz.height());
    return (style()->sizeFromContents(QStyle::CT_PushButton, &option, QSize(w, h), this).
            expandedTo(QApplication::globalStrut()));
}

void FlatButton::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    updateOverlayGeometry();
}

void FlatButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStylePainter painter(this);

    QStyleOptionButton option(getStyleOption());

    painter.drawControl(QStyle::CE_PushButton, option);

    if (underMouse()) {
        QRect r(rect());
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        painter.setOpacity(0.1);
        painter.fillRect(r, brush);
    }
}

void FlatButton::mousePressEvent(QMouseEvent *event)
{
    if (!_overlay)
        return;

    _overlay->addRipple(event->pos());
}

void FlatButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    emit clicked();
}

void FlatButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    update();
}

void FlatButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    update();
}

QStyleOptionButton FlatButton::getStyleOption() const
{
    QStyleOptionButton option;
    option.initFrom(this);
    option.features = QStyleOptionButton::Flat;
    if (isChecked())
        option.state |= QStyle::State_On;
    option.text = text();
    option.icon = icon();
    option.iconSize = iconSize();
    return option;
}
