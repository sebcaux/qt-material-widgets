#include "sliderthumb.h"
#include <QEvent>
#include <QPainter>
#include <QDebug>
#include "lib/style.h"
#include "slider.h"

SliderThumb::SliderThumb(Slider *slider)
    : QWidget(slider->parentWidget()),
      slider(slider),
      _diameter(11),
      _borderWidth(2),
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
    QEvent::Type type = event->type();

    if (QEvent::ParentChange == type) {
        setParent(slider->parentWidget());
    } else if (QEvent::Resize == type || QEvent::Move == type) {
        QWidget *widget;
        if ((widget = parentWidget())) {
            setGeometry(widget->rect());
        }
    }
    return QWidget::eventFilter(obj, event);
}

void SliderThumb::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Halo

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(_haloColor);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    painter.setRenderHint(QPainter::Antialiasing);

    QPointF disp = Qt::Horizontal == slider->orientation()
        ? QPointF(SLIDER_MARGIN + slider->thumbOffset(), slider->height()/2)
        : QPointF(slider->width()/2, SLIDER_MARGIN + slider->thumbOffset());

    QRectF halo((slider->pos() - QPointF(_haloSize, _haloSize)/2) + disp,
                QSizeF(_haloSize, _haloSize));

    painter.drawEllipse(halo);

    // Knob

    brush.setColor(slider->value() > slider->minimum()
       ? (slider->isEnabled()
          ? _fillColor : Style::instance().themeColor("disabled"))
       : _minFillColor);
    painter.setBrush(brush);

    if (_borderWidth > 0) {
        QPen pen;
        pen.setColor(Style::instance().themeColor("accent3"));
        pen.setWidthF(_borderWidth);
        painter.setPen(pen);
    } else {
        painter.setPen(Qt::NoPen);
    }

    QRectF geometry = Qt::Horizontal == slider->orientation()
        ? QRectF(slider->thumbOffset(), slider->height()/2 - SLIDER_MARGIN,
                 SLIDER_MARGIN*2, SLIDER_MARGIN*2).translated(slider->pos())
        : QRectF(slider->width()/2 - SLIDER_MARGIN, slider->thumbOffset(),
                 SLIDER_MARGIN*2, SLIDER_MARGIN*2).translated(slider->pos());

    QRectF thumb(0, 0, _diameter, _diameter);

    thumb.moveCenter(geometry.center());

    painter.drawEllipse(thumb);

#ifdef DEBUG_LAYOUT
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

    painter.drawRect(geometry);

    painter.drawRect(rect().adjusted(0, 0, -2, -2));
#endif

    QWidget::paintEvent(event);
}
