#include "progress.h"
#include "progress_p.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>
#include "progress_internal.h"
#include "lib/style.h"

ProgressPrivate::ProgressPrivate(Progress *q)
    : q_ptr(q),
      delegate(new ProgressDelegate(q)),
      progressType(Material::IndeterminateProgress),
      useThemeColors(true)
{
}

ProgressPrivate::~ProgressPrivate()
{
}

void ProgressPrivate::init()
{
    Q_Q(Progress);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("offset");
    animation->setTargetObject(delegate);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setDuration(1000);

    animation->setLoopCount(-1);

    animation->start();
}

Progress::Progress(QWidget *parent)
    : QProgressBar(parent),
      d_ptr(new ProgressPrivate(this))
{
    d_func()->init();
}

Progress::~Progress()
{
}

void Progress::setProgressType(Material::ProgressType type)
{
    Q_D(Progress);

    d->progressType = type;
    update();
}

Material::ProgressType Progress::progressType() const
{
    Q_D(const Progress);

    return d->progressType;
}

void Progress::setUseThemeColors(bool state)
{
    Q_D(Progress);

    d->useThemeColors = state;
    update();
}

bool Progress::useThemeColors() const
{
    Q_D(const Progress);

    return d->useThemeColors;
}

void Progress::setProgressColor(const QColor &color)
{
    Q_D(Progress);

    d->progressColor = color;
    setUseThemeColors(false);
}

QColor Progress::progressColor() const
{
    Q_D(const Progress);

    if (d->useThemeColors || !d->progressColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->progressColor;
    }
}

void Progress::setBackgroundColor(const QColor &color)
{
    Q_D(Progress);

    d->backgroundColor = color;
    setUseThemeColors(false);
}

QColor Progress::backgroundColor() const
{
    Q_D(const Progress);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return Style::instance().themeColor("border");
    } else {
        return d->backgroundColor;
    }
}

void Progress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(Progress);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(isEnabled() ? backgroundColor()
                               : Style::instance().themeColor("disabled"));
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    QPainterPath path;
    path.addRoundedRect(0, height()/2-3, width(), 6, 3, 3);
    painter.setClipPath(path);

    painter.drawRect(0, 0, width(), height());

    if (isEnabled())
    {
        brush.setColor(progressColor());
        painter.setBrush(brush);

        if (Material::IndeterminateProgress == d->progressType) {
            painter.drawRect(d->delegate->offset()*width()*2-width(), 0, width(), height());
        } else {
            qreal p = static_cast<qreal>(width())*(value()-minimum())/(maximum()-minimum());
            painter.drawRect(0, 0, p, height());
        }
    }
}
