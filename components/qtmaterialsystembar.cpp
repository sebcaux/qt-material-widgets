#include "qtmaterialsystembar.h"

#include "lib/qtmaterialstyle.h"
#include "lib/qtmaterialtheme.h"
#include "qtmaterialsystembar_p.h"

#include <QBasicTimer>
#include <QDateTime>
#include <QEvent>
#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>

/*!
 *  \QtMaterialSystemBarPrivate
 *  \internal
 */

QtMaterialSystemBarPrivate::QtMaterialSystemBarPrivate(QtMaterialSystemBar *q)
    : q_ptr(q)
{
}

QtMaterialSystemBarPrivate::~QtMaterialSystemBarPrivate()
{
    delete timer;
}

void QtMaterialSystemBarPrivate::init()
{
    Q_Q(QtMaterialSystemBar);

    timer = new QBasicTimer();
    timer->start(500, Qt::VeryCoarseTimer, q);

    dateTimeFormat = QLatin1String("dd/MM/yyyy hh:mm:ss");
    useThemeColors = true;

    q->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    q->setFont(QtMaterialStyle::instance().themeFont(Material::FontBody1));
}

/*!
 *  \QtMaterialSystemBar
 */

QtMaterialSystemBar::QtMaterialSystemBar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialSystemBarPrivate(this))
{
    d_func()->init();
}

QtMaterialSystemBar::~QtMaterialSystemBar()
{
}

const QString &QtMaterialSystemBar::dateTimeFormat() const
{
    Q_D(const QtMaterialSystemBar);

    return d->dateTimeFormat;
}

void QtMaterialSystemBar::setDateTimeFormat(const QString &dateTimeFormat)
{
    Q_D(QtMaterialSystemBar);

    d->dateTimeFormat = dateTimeFormat;
    update();
}

void QtMaterialSystemBar::setUseThemeColors(bool value)
{
    Q_D(QtMaterialSystemBar);

    if (d->useThemeColors == value)
    {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialSystemBar::useThemeColors() const
{
    Q_D(const QtMaterialSystemBar);

    return d->useThemeColors;
}

void QtMaterialSystemBar::setTextColor(const QColor &color)
{
    Q_D(QtMaterialSystemBar);

    d->textColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialSystemBar::textColor() const
{
    Q_D(const QtMaterialSystemBar);

    if (d->useThemeColors || !d->textColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeAlternateText);
    }

    return d->textColor;
}

void QtMaterialSystemBar::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialSystemBar);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialSystemBar::backgroundColor() const
{
    Q_D(const QtMaterialSystemBar);

    if (d->useThemeColors || !d->backgroundColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeText);
    }

    return d->backgroundColor;
}

/*!
 *  \reimp
 */
bool QtMaterialSystemBar::event(QEvent *event)
{
    if (event->type() == QEvent::FontChange)
    {
        updateGeometry();
    }
    return QWidget::event(event);
}

/*!
 *  \reimp
 */
void QtMaterialSystemBar::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    update();
}

/*!
 *  \reimp
 */
QSize QtMaterialSystemBar::sizeHint() const
{
    return QSize(-1, fontMetrics().height() + 10);
}

/*!
 *  \reimp
 */
void QtMaterialSystemBar::paintEvent(QPaintEvent *event)
{
    Q_D(const QtMaterialSystemBar);

    Q_UNUSED(event);

    const QString &dateTimeStr(QDateTime::currentDateTime().toString(d->dateTimeFormat));

    QPainter painter(this);

    painter.setPen(QPen(Qt::NoPen));
    painter.setBrush(backgroundColor());
    painter.drawRect(rect());

    painter.setPen(textColor());
    painter.drawText(rect(), Qt::AlignCenter, dateTimeStr);
}
