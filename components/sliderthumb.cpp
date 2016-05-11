#include "sliderthumb.h"
#include <QEvent>
#include <QPainter>
#include "slider.h"

// change
#define THUMB_OUTER_SIZE 20

SliderThumb::SliderThumb(Slider *slider)
    : QWidget(slider->parentWidget()),
      slider(slider),
      _diameter(11),
      _borderWidth(0),
      _fillColor(Qt::white),
      _minFillColor(Qt::white),
      _haloSize(0)
{
    slider->installEventFilter(this);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);

    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(update()));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(update()));
}

SliderThumb::~SliderThumb()
{
}

bool SliderThumb::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::ParentChange == event->type()) {
        setParent(slider->parentWidget());
    }
    return QWidget::eventFilter(obj, event);
}

void SliderThumb::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Halo

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0, 0, 0, 20));
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    painter.setRenderHint(QPainter::Antialiasing);

    QPointF disp = Qt::Horizontal == slider->orientation()
        ? QPointF(THUMB_OUTER_SIZE/2 + slider->thumbOffset(),
                  slider->height()/2)
        : QPointF(slider->width()/2,
                  THUMB_OUTER_SIZE/2 + slider->thumbOffset());

    QRectF halo((slider->pos() - QPointF(_haloSize, _haloSize)/2) + disp,
                QSizeF(_haloSize, _haloSize));

    painter.drawEllipse(halo);

    // Knob

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(slider->sliderPosition() > slider->minimum()
       ? _fillColor : _minFillColor);
    painter.setBrush(brush);

    if (_borderWidth > 0) {
        QPen pen;
        pen.setWidthF(_borderWidth);
        painter.setPen(pen);
    } else {
        painter.setPen(Qt::NoPen);
    }

    QRectF geometry = Qt::Horizontal == slider->orientation()
        ? QRectF(slider->thumbOffset(), slider->height()/2 - THUMB_OUTER_SIZE/2,
                 THUMB_OUTER_SIZE, THUMB_OUTER_SIZE).translated(slider->pos())
        : QRectF(slider->width()/2 - THUMB_OUTER_SIZE/2, slider->thumbOffset(),
                 THUMB_OUTER_SIZE, THUMB_OUTER_SIZE).translated(slider->pos());

    QRectF thumb(0, 0, _diameter, _diameter);

    thumb.moveCenter(geometry.center());

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
