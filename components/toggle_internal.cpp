#include "toggle_internal.h"
#include <QPainter>
#include <QEvent>
#include <QGraphicsDropShadowEffect>
#include "lib/style.h"
#include "lib/rippleoverlay.h"
#include "toggle.h"
#include "toggle_p.h"

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
    updateOffset();
}

bool ToggleThumb::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();
    if (QEvent::Resize == type || QEvent::Move == type) {
        setGeometry(parentWidget()->rect().adjusted(8, 8, -8, -8));
        updateOffset();
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
    brush.setColor(_toggle->isEnabled() ? _thumbColor : Qt::white);

    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    int s;
    QRectF r;

    if (Qt::Horizontal == _toggle->orientation()) {
        s = height()-10;
        r = QRectF(5+_offset, 5, s, s);
    } else {
        s = width()-10;
        r = QRectF(5, 5+_offset, s, s);
    }

    painter.drawEllipse(r);

    if (!_toggle->isEnabled()) {
        brush.setColor(_toggle->disabledColor());
        painter.setBrush(brush);
        painter.drawEllipse(r);
    }
}

void ToggleThumb::updateOffset()
{
    const QSize s(Qt::Horizontal == _toggle->orientation()
        ? size() : size().transposed());
    _offset = shift()*static_cast<qreal>(s.width()-s.height());

    _toggle->updateOverlayGeometry();
    update();
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

void ToggleTrack::setTrackColor(const QColor &color)
{
    _trackColor = color;
    _toggle->d_func()->ripple->setColor(color);
    update();
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
    if (_toggle->isEnabled()) {
        brush.setColor(_trackColor);
        painter.setOpacity(0.8);
    } else {
        QColor disabledColor(Style::instance().themeColor("disabled"));
        brush.setColor(disabledColor);
        painter.setOpacity(0.6);
    }
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
