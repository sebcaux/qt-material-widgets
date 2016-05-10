#include "sliderthumb.h"
#include "slider_p.h"

SliderThumb::SliderThumb(SliderPrivate *slider)
    : QWidget(slider->q_func()),
      slider(slider),
      _haloSize(0)
{
    Slider *parent = slider->q_func();

    parent->installEventFilter(this);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);

    connect(parent, SIGNAL(sliderMoved(int)), this, SLOT(update()));
    connect(parent, SIGNAL(valueChanged(int)), this, SLOT(update()));
}

SliderThumb::~SliderThumb()
{
}

bool SliderThumb::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::ParentChange == event->type()) {
        setParent(slider->q_func()->parentWidget());
    }
    return QWidget::eventFilter(obj, event);
}

void SliderThumb::paintEvent(QPaintEvent *event)
{
    Slider *const q = slider->q_func();

    QPainter painter(this);

    // Halo

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0, 0, 0, 20));
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    painter.setRenderHint(QPainter::Antialiasing);

    QPointF disp = Qt::Horizontal == q->orientation()
        ? QPointF(THUMB_OUTER_SIZE/2 + q->thumbOffset(),
                  q->height()/2)
        : QPointF(q->width()/2,
                  THUMB_OUTER_SIZE/2 + q->thumbOffset());

    QRectF halo((q->pos() - QPointF(_haloSize, _haloSize)/2) + disp,
                QSize(_haloSize, _haloSize));

    painter.drawEllipse(halo);

    // Knob

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(slider->thumbColor);
    painter.setBrush(brush);

    if (slider->thumbPenWidth > 0) {
        QPen pen;
        pen.setWidthF(slider->thumbPenWidth);
        painter.setPen(pen);
    } else {
        painter.setPen(Qt::NoPen);
    }

    QRectF thumb(0, 0, slider->thumbSize, slider->thumbSize);
    thumb.moveCenter(thumbGeometry().center());

    painter.drawEllipse(thumb);

#ifdef DEBUG_LAYOUT
        QPen pen;
        pen.setColor(Qt::red);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        painter.drawRect(rect().adjusted(0, 0, -2, -2));
#endif

    QWidget::paintEvent(event);
}

QRectF SliderThumb::thumbGeometry() const
{
    const Slider *const q = slider->q_func();

    return Qt::Horizontal == q->orientation()
        ? QRectF(q->thumbOffset(), q->rect().height()/2 - THUMB_OUTER_SIZE/2,
                 THUMB_OUTER_SIZE, THUMB_OUTER_SIZE)
        : QRectF(q->rect().width()/2 - THUMB_OUTER_SIZE/2, q->thumbOffset(),
                 THUMB_OUTER_SIZE, THUMB_OUTER_SIZE);
}
