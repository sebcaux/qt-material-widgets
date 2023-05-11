#include "qtmaterialcanvas.h"

#include "lib/qtmaterialstyle.h"
#include "qtmaterialcanvas_p.h"
#include "qtmaterialscrollbar.h"

#include <QPainter>
#include <QScroller>

#if QT_VERSION >= 0x060000
#    include <QInputDevice>
#else
#    include <QTouchDevice>
#endif

/*!
 *  \class QtMaterialCanvasPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialCanvasPrivate::QtMaterialCanvasPrivate(QtMaterialCanvas *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
void QtMaterialCanvasPrivate::init()
{
    Q_Q(QtMaterialCanvas);

    orientation = Qt::Vertical;
    useThemeColors = true;

    q->setFrameShape(QFrame::NoFrame);

#if QT_VERSION >= 0x060000
    QList<const QInputDevice *> touchDevices;
    for (const QInputDevice *inputDevice : QInputDevice::devices())
    {
        if (inputDevice->type() == QInputDevice::DeviceType::TouchScreen)
        {
            touchDevices.append(inputDevice);
        }
    }
    if (touchDevices.isEmpty())
#else
    if (QTouchDevice::devices().isEmpty())
#endif
    {
        QScroller::grabGesture(q->viewport(), QScroller::LeftMouseButtonGesture);
    }
    else
    {
        QScroller::grabGesture(q->viewport(), QScroller::TouchGesture);
    }
}

/*!
 *  \internal
 */
void QtMaterialCanvasPrivate::updateOrientation()
{
    Q_Q(QtMaterialCanvas);

    QScrollerProperties ScrollerProperties = QScroller::scroller(q->viewport())->scrollerProperties();

    if (orientation == Qt::Vertical)
    {
        q->setVerticalScrollBar(new QtMaterialScrollBar(orientation));
        q->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ScrollerProperties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, QScrollerProperties::OvershootAlwaysOn);
        ScrollerProperties.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
    }
    else
    {
        q->setHorizontalScrollBar(new QtMaterialScrollBar(orientation));
        q->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ScrollerProperties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
        ScrollerProperties.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy, QScrollerProperties::OvershootAlwaysOn);
    }

    ScrollerProperties.setScrollMetric(QScrollerProperties::OvershootDragResistanceFactor, 0.1);
    ScrollerProperties.setScrollMetric(QScrollerProperties::OvershootDragDistanceFactor, 0.1);
    ScrollerProperties.setScrollMetric(QScrollerProperties::OvershootScrollDistanceFactor, 0.1);
    QScroller::scroller(q->viewport())->setScrollerProperties(ScrollerProperties);
}

/*!
 *  \internal
 */
QtMaterialCanvasPrivate::~QtMaterialCanvasPrivate()
{
}

/*!
 *  \class QtMaterialCanvas
 */

QtMaterialCanvas::QtMaterialCanvas(QWidget *parent)
    : QScrollArea(parent),
      d_ptr(new QtMaterialCanvasPrivate(this))
{
    d_func()->init();
    d_func()->updateOrientation();
}

QtMaterialCanvas::QtMaterialCanvas(Qt::Orientation orientation, QWidget *parent)
    : QScrollArea(parent),
      d_ptr(new QtMaterialCanvasPrivate(this))
{
    d_func()->init();
    setOrientation(orientation);
}

QtMaterialCanvas::~QtMaterialCanvas()
{
}

Qt::Orientation QtMaterialCanvas::orientation() const
{
    Q_D(const QtMaterialCanvas);

    return d->orientation;
}

void QtMaterialCanvas::setOrientation(Qt::Orientation orientation)
{
    Q_D(QtMaterialCanvas);

    d->orientation = orientation;
    d_func()->updateOrientation();
}

bool QtMaterialCanvas::useThemeColors() const
{
    Q_D(const QtMaterialCanvas);

    return d->useThemeColors;
}

void QtMaterialCanvas::setUseThemeColors(bool value)
{
    Q_D(QtMaterialCanvas);

    if (d->useThemeColors == value)
    {
        return;
    }

    d->useThemeColors = value;
    update();
}

QColor QtMaterialCanvas::backgroundColor() const
{
    Q_D(const QtMaterialCanvas);

    if (d->useThemeColors || !d->backgroundColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeCanvas);
    }

    return d->backgroundColor;
}

void QtMaterialCanvas::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialCanvas);

    d->backgroundColor = color;

    if (d->useThemeColors)
    {
        d->useThemeColors = false;
    }
    update();
}

void QtMaterialCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(viewport());

    painter.fillRect(rect(), backgroundColor());
}
