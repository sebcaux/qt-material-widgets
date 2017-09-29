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

    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(update()));
}

SliderTrack::~SliderTrack()
{
}

bool SliderTrack::eventFilter(QObject *obj, QEvent *event)
{
    QEvent::Type type = event->type();

    if (QEvent::ParentChange == type) {
        setParent(slider->parentWidget());
    } else if (QEvent::Resize == type || QEvent::Move == type) {
        if (parentWidget()) {
            setGeometry(parentWidget()->rect());
        }
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
    bg.setColor(slider->isEnabled() ? _fillColor
                                    : style.themeColor("disabled"));

    painter.setRenderHint(QPainter::Antialiasing);

    qreal offset = slider->thumbOffset();

    if (Qt::Horizontal == slider->orientation()) {
        painter.translate(slider->x() + SLIDER_MARGIN,
                          slider->y() + slider->height()/2
                                      - static_cast<qreal>(_width)/2);
    } else {
        painter.translate(slider->x() + slider->width()/2
                                      - static_cast<qreal>(_width)/2,
                          slider->y() + SLIDER_MARGIN);
    }

    QRectF geometry = Qt::Horizontal == slider->orientation()
        ? QRectF(0, 0, slider->width() - SLIDER_MARGIN*2, _width)
        : QRectF(0, 0, _width, slider->height() - SLIDER_MARGIN*2);

    QRectF bgRect;
    QRectF fgRect;

    if (Qt::Horizontal == slider->orientation()) {
        fgRect = QRectF(0, 0, offset, _width);
        bgRect = QRectF(offset, 0, slider->width(), _width).intersected(geometry);
    } else {
        fgRect = QRectF(0, 0, _width, offset);
        bgRect = QRectF(0, offset, _width, slider->height()).intersected(geometry);
    }

    if (!slider->isEnabled()) {
        fgRect = fgRect.width() < 9 ? QRectF() : fgRect.adjusted(0, 0, -6, 0);
        bgRect = bgRect.width() < 9 ? QRectF() : bgRect.adjusted(6, 0, 0, 0);
    }

    if (slider->invertedAppearance()) {
        qSwap(bgRect, fgRect);
    }

    painter.fillRect(bgRect, bg);
    painter.fillRect(fgRect, fg);

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
