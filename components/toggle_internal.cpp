#include <QPainter>
#include <QEvent>
#include <QGraphicsDropShadowEffect>
#include "lib/style.h"
#include "toggle_internal.h"
#include "toggle.h"

ToggleThumb::ToggleThumb(Toggle *parent)
    : QWidget(parent),
      _toggle(parent),
      _shift(0),
      _offset(0)
{
    parent->installEventFilter(this);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;

    effect->setBlurRadius(6);
    effect->setColor(QColor(0, 0, 0, 80));
    effect->setOffset(QPointF(0, 1));

    setGraphicsEffect(effect);
}

ToggleThumb::~ToggleThumb()
{
}

void ToggleThumb::setShift(qreal shift)
{
    if (_shift == shift)
        return;

    _shift = shift;

    const QSize s(Qt::Horizontal == _toggle->orientation()
            ? size() : size().transposed());

    _offset = shift*static_cast<qreal>(s.width()-s.height());
    _toggle->updateOverlayGeometry();
    update();
}

bool ToggleThumb::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();
    if (QEvent::Resize == type || QEvent::Move == type) {
        setGeometry(parentWidget()->rect().adjusted(8, 8, -8, -8));
    } else if (QEvent::MouseButtonPress == type) {
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void ToggleThumb::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if (_toggle->isEnabled()) {
        brush.setColor(_thumbColor);
    } else {
        QColor disabledColor = Style::instance().themeColor("accent3");
        brush.setColor(disabledColor.lighter(140));
    }
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    if (Qt::Horizontal == _toggle->orientation()) {
        const int s = height()-10;
        painter.drawEllipse(QRectF(5+_offset, 5, s, s));
    } else {
        const int s = width()-10;
        painter.drawEllipse(QRectF(5, 5+_offset, s, s));
    }
}

void ToggleThumb::mouseReleaseEvent(QMouseEvent *event)
{
    if (_toggle->isEnabled()) {
        const bool newChecked = !_toggle->isChecked();
        _toggle->setChecked(newChecked);
        emit clicked(newChecked);
    }
    QWidget::mouseReleaseEvent(event);
}

ToggleTrack::ToggleTrack(Toggle *parent)
    : QWidget(parent),
      _toggle(parent)
{
    parent->installEventFilter(this);
}

ToggleTrack::~ToggleTrack()
{
}

bool ToggleTrack::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();
    if (QEvent::Resize == type || QEvent::Move == type) {
        setGeometry(parentWidget()->rect());
    }
    return QWidget::eventFilter(obj, event);
}

void ToggleTrack::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setColor(_trackColor);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    painter.setPen(Qt::NoPen);

    if (Qt::Horizontal == _toggle->orientation()) {
        const int h = height()/2;
        const QRect r(0, h/2, width(), h);
        painter.drawRoundedRect(r.adjusted(14, 4, -14, -4), h/2-4, h/2-4);
    } else {
        const int w = width()/2;
        const QRect r(w/2, 0, w, height());
        painter.drawRoundedRect(r.adjusted(4, 14, -4, -14), w/2-4, w/2-4);
    }
}
