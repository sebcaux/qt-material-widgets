#include "scrollwidget.h"
#include "scrollwidget_p.h"
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include <QStyleOptionSlider>
#include "scrollwidget_internal.h"
//#include "lib/style.h"
#include "xxlib/qtmaterialstyle.h"
#include <QDebug>

ScrollBarPrivate::ScrollBarPrivate(ScrollBar *q)
    : q_ptr(q),
      machine(new ScrollBarStateMachine(q)),
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
    q->setStyle(&QtMaterialStyle::instance());
    q->setStyleSheet("QScrollBar:vertical { margin: 0; }"
                     "QScrollBar::add-line:vertical { height: 0; margin: 0; }"
                     "QScrollBar::sub-line:vertical { height: 0; margin: 0; }");

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

void ScrollBar::setCanvasColor(const QColor &color)
{
    Q_D(ScrollBar);

    d->canvasColor = color;
    setUseThemeColors(false);
}

QColor ScrollBar::canvasColor() const
{
    Q_D(const ScrollBar);

    if (d->useThemeColors || !d->canvasColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    } else {
        return d->canvasColor;
    }
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
        return QtMaterialStyle::instance().themeColor("border").darker(110);
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
        return QtMaterialStyle::instance().themeColor("primary1");
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

//void ScrollBar::mousePressEvent(QMouseEvent *event)
//{
//    /* Map event position coordinates to actual scrollbar's geometry */
//    QMouseEvent e(translateEventGeometry(event));
//
//    QScrollBar::mousePressEvent(&e);
//}
//
//void ScrollBar::mouseMoveEvent(QMouseEvent *event)
//{
//    /* Map event position coordinates to actual scrollbar's geometry */
//    QMouseEvent e(translateEventGeometry(event));
//
//    QScrollBar::mouseMoveEvent(&e);
//}

void ScrollBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(ScrollBar);

    QPainter painter(this);

    painter.fillRect(rect(), canvasColor());

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

//QMouseEvent ScrollBar::translateEventGeometry(QMouseEvent *event)
//{
//    //QStyleOptionSlider *option = new QStyleOptionSlider;
//    //option->initFrom(this);
//
//    //qDebug() << style()->subControlRect(QStyle::CC_ScrollBar,option,QStyle::SC_ScrollBarSubLine,this);
//
//    const qreal btnSize = 20;           // @TODO
//
//    QPoint localPos;
//    if (Qt::Horizontal == orientation()) {
//        const qreal x = width();
//        localPos = QPoint(btnSize + (event->x()*(x-2*btnSize)/x), event->y());
//    } else {
//        const qreal y = height();
//        localPos = QPoint(event->x(), btnSize + (event->y()*(y-2*btnSize)/y));
//    }
//
//    QPoint screenPos = mapToGlobal(localPos);
//    QPoint windowPos = window()->mapFromGlobal(screenPos);
//
//    return QMouseEvent(event->type(),
//                       localPos,
//                       windowPos,
//                       screenPos,
//                       event->button(),
//                       event->buttons(),
//                       event->modifiers());
//}
