#include "qtmaterialpaper.h"

#include "lib/qtmaterialstyle.h"
#include "qtmaterialpaper_p.h"

#include <QPainter>

/*!
 *  \class QtMaterialPaperPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialPaperPrivate::QtMaterialPaperPrivate(QtMaterialPaper *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
void QtMaterialPaperPrivate::init()
{
    useThemeColors = true;
}

/*!
 *  \internal
 */
QtMaterialPaperPrivate::~QtMaterialPaperPrivate()
{
}

/*!
 *  \class QtMaterialPaper
 */

QtMaterialPaper::QtMaterialPaper(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialPaperPrivate(this))
{
    d_func()->init();
}

QtMaterialPaper::~QtMaterialPaper()
{
}

bool QtMaterialPaper::useThemeColors() const
{
    Q_D(const QtMaterialPaper);

    return d->useThemeColors;
}

void QtMaterialPaper::setUseThemeColors(bool value)
{
    Q_D(QtMaterialPaper);

    if (d->useThemeColors == value)
    {
        return;
    }

    d->useThemeColors = value;
    update();
}

QColor QtMaterialPaper::backgroundColor() const
{
    Q_D(const QtMaterialPaper);

    if (d->useThemeColors || !d->backgroundColor.isValid())
    {
        QColor bColor = QtMaterialStyle::instance().themeColor(Material::ColorThemeCanvas);
        if (bColor.black() > 127)
        {
            bColor = bColor.lighter(130);
        }
        else
        {
            bColor = bColor.darker(120);
        }
        return bColor;
    }

    return d->backgroundColor;
}

void QtMaterialPaper::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialPaper);

    d->backgroundColor = color;

    if (d->useThemeColors)
    {
        d->useThemeColors = false;
    }
    update();
}

void QtMaterialPaper::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(backgroundColor());
    painter.drawRoundedRect(rect(), 5, 5);
}
