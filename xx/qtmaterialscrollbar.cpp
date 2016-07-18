#include "xx/qtmaterialscrollbar.h"
#include "xx/qtmaterialscrollbar_p.h"
#include <QPainter>
#include "xx/qtmaterialscrollbar_internal.h"
#include "xxlib/qtmaterialstyle.h"

/*!
 *  \class QtMaterialScrollBarPrivate
 *  \internal
 */

QtMaterialScrollBarPrivate::QtMaterialScrollBarPrivate(QtMaterialScrollBar *q)
    : q_ptr(q)
{
}

QtMaterialScrollBarPrivate::~QtMaterialScrollBarPrivate()
{
}

void QtMaterialScrollBarPrivate::init()
{
    Q_Q(QtMaterialScrollBar);

    stateMachine   = new QtMaterialScrollBarStateMachine(q);
    hideOnMouseOut = true;
    useThemeColors = true;

    q->setMouseTracking(true);
    q->setStyle(&QtMaterialStyle::instance());
    q->setStyleSheet("QScrollBar:vertical { margin: 0; }"
                     "QScrollBar::add-line:vertical { height: 0; margin: 0; }"
                     "QScrollBar::sub-line:vertical { height: 0; margin: 0; }");

    stateMachine->start();
}

/*!
 *  \class QtMaterialScrollBar
 */

QtMaterialScrollBar::QtMaterialScrollBar(QWidget *parent)
    : QScrollBar(parent),
      d_ptr(new QtMaterialScrollBarPrivate(this))
{
    d_func()->init();
}

QtMaterialScrollBar::~QtMaterialScrollBar()
{
}

/*!
 *  \reimp
 */
QSize QtMaterialScrollBar::sizeHint() const
{
    if (Qt::Horizontal == orientation()) {
        return QSize(1, 10);
    } else {
        return QSize(10, 1);
    }
}

void QtMaterialScrollBar::setUseThemeColors(bool value)
{
    Q_D(QtMaterialScrollBar);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialScrollBar::useThemeColors() const
{
    Q_D(const QtMaterialScrollBar);

    return d->useThemeColors;
}

void QtMaterialScrollBar::setCanvasColor(const QColor &color)
{
    Q_D(QtMaterialScrollBar);

    d->canvasColor = color;
    setUseThemeColors(false);
}

QColor QtMaterialScrollBar::canvasColor() const
{
    Q_D(const QtMaterialScrollBar);

    if (d->useThemeColors || !d->canvasColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    } else {
        return d->canvasColor;
    }
}

void QtMaterialScrollBar::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialScrollBar);

    d->backgroundColor = color;
    setUseThemeColors(false);
}

QColor QtMaterialScrollBar::backgroundColor() const
{
    Q_D(const QtMaterialScrollBar);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("border");
    } else {
        return d->backgroundColor;
    }
}

void QtMaterialScrollBar::setSliderColor(const QColor &color)
{
    Q_D(QtMaterialScrollBar);

    d->sliderColor = color;
    setUseThemeColors(false);
}

QColor QtMaterialScrollBar::sliderColor() const
{
    Q_D(const QtMaterialScrollBar);

    if (d->useThemeColors || !d->sliderColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    } else {
        return d->sliderColor;
    }
}

void QtMaterialScrollBar::setHideOnMouseOut(bool value)
{
    Q_D(QtMaterialScrollBar);

    d->hideOnMouseOut = value;
    update();
}

bool QtMaterialScrollBar::hideOnMouseOut() const
{
    Q_D(const QtMaterialScrollBar);

    return d->hideOnMouseOut;
}

/*!
 *  \reimp
 */
void QtMaterialScrollBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialScrollBar);

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
        painter.setOpacity(d->stateMachine->opacity());
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
