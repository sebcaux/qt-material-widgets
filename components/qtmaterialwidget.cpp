#include "qtmaterialwidget.h"

#include "lib/qtmaterialstyle.h"
#include "qtmaterialwidget_p.h"

#include <QPainter>

/*!
 *  \class QtMaterialWidgetPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialWidgetPrivate::QtMaterialWidgetPrivate(QtMaterialWidget *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
void QtMaterialWidgetPrivate::init()
{
    useThemeColors = true;
}

/*!
 *  \internal
 */
QtMaterialWidgetPrivate::~QtMaterialWidgetPrivate()
{
}

/*!
 *  \class QtMaterialWidget
 */

QtMaterialWidget::QtMaterialWidget(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialWidgetPrivate(this))
{
    d_func()->init();
}

QtMaterialWidget::~QtMaterialWidget()
{
}

bool QtMaterialWidget::useThemeColors() const
{
    Q_D(const QtMaterialWidget);

    return d->useThemeColors;
}

void QtMaterialWidget::setUseThemeColors(bool value)
{
    Q_D(QtMaterialWidget);

    if (d->useThemeColors == value)
    {
        return;
    }

    d->useThemeColors = value;
    update();
}

QColor QtMaterialWidget::backgroundColor() const
{
    Q_D(const QtMaterialWidget);

    if (d->useThemeColors || !d->backgroundColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeCanvas);
    }

    return d->backgroundColor;
}

void QtMaterialWidget::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialWidget);

    d->backgroundColor = color;

    if (d->useThemeColors)
    {
        d->useThemeColors = false;
    }
    update();
}

void QtMaterialWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.fillRect(rect(), backgroundColor());
}
