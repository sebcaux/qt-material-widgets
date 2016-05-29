#include <QPainter>
#include <QEvent>
#include <QGraphicsDropShadowEffect>
#include "toggle_internal.h"
#include "toggle.h"

Thumb::Thumb(Toggle *parent)
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

Thumb::~Thumb()
{
}

void Thumb::setShift(qreal shift)
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

bool Thumb::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();
    if (QEvent::Resize == type || QEvent::Move == type) {
        setGeometry(parentWidget()->rect().adjusted(8, 8, -8, -8));
    } //else if (QEvent::MouseButtonRelease == type) {
        //return true;
    //}
    return QWidget::eventFilter(obj, event);
}

void Thumb::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
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

void Thumb::mouseReleaseEvent(QMouseEvent *event)
{
    if (_toggle->isEnabled()) {
        _toggle->setChecked(!_toggle->isChecked());
        emit clicked();
    }
    QWidget::mouseReleaseEvent(event);
}
