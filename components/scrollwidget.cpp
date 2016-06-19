#include "scrollwidget.h"
#include "scrollwidget_p.h"
#include <QPainter>
#include <QApplication>
#include "scrollwidget_internal.h"
#include "lib/style.h"

ScrollBarPrivate::ScrollBarPrivate(ScrollBar *q)
    : q_ptr(q),
      machine(0),
      hideOnMouseOut(true),
      useThemeColors(true)
{
}

ScrollBarPrivate::~ScrollBarPrivate()
{
}

void ScrollBarPrivate::init()
{
    Q_Q(ScrollBar);

    q->setMouseTracking(true);

    machine = new ScrollBarStateMachine(q);
    machine->start();

    QCoreApplication::processEvents();
}

ScrollBar::ScrollBar(QWidget *parent)
    : QScrollBar(parent),
      d_ptr(new ScrollBarPrivate(this))
{
    d_func()->init();
}

ScrollBar::~ScrollBar()
{
}

void ScrollBar::setUseThemeColors(bool value)
{
    Q_D(ScrollBar);

    d->useThemeColors = value;
    update();
}

bool ScrollBar::useThemeColors() const
{
    Q_D(const ScrollBar);

    return d->useThemeColors;
}

void ScrollBar::setBackgroundColor(const QColor &color)
{
    Q_D(ScrollBar);

    d->backgroundColor = color;
    setUseThemeColors(false);
}

QColor ScrollBar::backgroundColor() const
{
    Q_D(const ScrollBar);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return Style::instance().themeColor("border").darker(110);
    } else {
        return d->backgroundColor;
    }
}

void ScrollBar::setSliderColor(const QColor &color)
{
    Q_D(ScrollBar);

    d->sliderColor = color;
    setUseThemeColors(false);
}

QColor ScrollBar::sliderColor() const
{
    Q_D(const ScrollBar);

    if (d->useThemeColors || !d->sliderColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->sliderColor;
    }
}

void ScrollBar::setHideOnMouseOut(bool state)
{
    Q_D(ScrollBar);

    d->hideOnMouseOut = state;
    update();
}

bool ScrollBar::hideOnMouseOut() const
{
    Q_D(const ScrollBar);

    return d->hideOnMouseOut;
}

QSize ScrollBar::sizeHint() const
{
    return QSize(10, 1);
}

void ScrollBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(ScrollBar);

    QPainter painter(this);

    painter.fillRect(rect(), palette().color(QPalette::Window));

    int x, y, w, h;
    rect().getRect(&x, &y, &w, &h);

    QMargins margins(2, 2, 2, 2);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(backgroundColor());
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    if (d->hideOnMouseOut) {
        painter.setOpacity(d->machine->opacity());
    }

    painter.drawRect(rect().marginsRemoved(margins));

    const qreal q = h / static_cast<qreal>(maximum() - minimum() + pageStep());

    QRect handle = Qt::Horizontal == orientation()
            ? QRect(sliderPosition()*q, y, pageStep()*q, h)
            : QRect(x, sliderPosition()*q, w, pageStep()*q);

    brush.setColor(sliderColor());
    painter.setBrush(brush);

    painter.drawRect(handle.marginsRemoved(margins));
}
