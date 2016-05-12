#include "slidertrack.h"
#include <QEvent>
#include <QPainter>
#include "lib/style.h"
#include "slider.h"

SliderTrack::SliderTrack(Slider *slider)
    : QWidget(slider->parentWidget()),
      slider(slider),
      _width(2)
{
    slider->installEventFilter(this);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

SliderTrack::~SliderTrack()
{
}

bool SliderTrack::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::ParentChange == event->type()) {
        setParent(slider->parentWidget());
    }
    return QWidget::eventFilter(obj, event);
}

void SliderTrack::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    Style &style = Style::instance();

    QBrush fg;
    fg.setStyle(Qt::SolidPattern);
    fg.setColor(slider->isEnabled() ? style.themeColor("primary1")
                                    : style.themeColor("disabled"));
    QBrush bg;
    bg.setStyle(Qt::SolidPattern);
    bg.setColor(slider->isEnabled() ? _fillColor : style.themeColor("disabled"));

    qreal offset = slider->thumbOffset();

    QSizeF box(slider->isEnabled() ? offset : offset - 7,
               qMax(slider->width(), slider->height()));

    if (Qt::Vertical == slider->orientation())
        box.transpose();

    QRectF rect = Qt::Vertical == slider->orientation()
        ? QRectF(0, slider->isEnabled() ? slider->y() + offset + SLIDER_MARGIN
                                        : slider->y() + offset + SLIDER_MARGIN + 7,
                 box.width(), box.width())
        : QRectF(slider->isEnabled() ? slider->x() + offset + SLIDER_MARGIN
                                     : slider->x() + offset + SLIDER_MARGIN + 7, 0,
                 box.height(), box.height());

    qreal hw = static_cast<qreal>(_width)/2;

    QRectF geometry = Qt::Horizontal == slider->orientation()
        ? QRectF(slider->x() + SLIDER_MARGIN,
                 slider->y() + slider->height()/2 - hw,
                 slider->width() - SLIDER_MARGIN*2,
                 hw*2)
        : QRectF(slider->x() + slider->width()/2 - hw,
                 slider->y() + SLIDER_MARGIN,
                 hw*2,
                 slider->height() - SLIDER_MARGIN*2);

    bool inverted = slider->invertedAppearance();

    QPointF pos = Qt::Horizontal == slider->orientation()
        ? QPointF(slider->x() + SLIDER_MARGIN, 0)
        : QPointF(0, slider->y() + SLIDER_MARGIN);

    painter.fillRect(QRectF(pos, box).intersected(geometry), inverted ? bg : fg);
    painter.fillRect(rect.intersected(geometry), inverted ? fg : bg);

#ifdef DEBUG_LAYOUT
    if (slider->hovered()) {
        painter.save();
        painter.setPen(Qt::red);
        painter.drawRect(geometry);
        painter.restore();
    }
#endif

    QWidget::paintEvent(event);
}
