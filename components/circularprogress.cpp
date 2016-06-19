#include "circularprogress.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include "circularprogress_p.h"
#include "circularprogress_internal.h"
#include "lib/style.h"

CircularProgressPrivate::CircularProgressPrivate(CircularProgress *q)
    : q_ptr(q),
      delegate(0),
      progressType(Material::IndeterminateProgress),
      size(64),
      angle(0),
      penWidth(6.25),
      useThemeColors(true)
{
}

CircularProgressPrivate::~CircularProgressPrivate()
{
}

void CircularProgressPrivate::init()
{
    Q_Q(CircularProgress);

    delegate = new CircularProgressDelegate(q);

    QSizePolicy policy(QSizePolicy::MinimumExpanding,
                       QSizePolicy::MinimumExpanding);
    q->setSizePolicy(policy);
    q->startTimer(4);

    QParallelAnimationGroup *group = new QParallelAnimationGroup(q);
    group->setLoopCount(-1);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("dashLength");
    animation->setTargetObject(delegate);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->setStartValue(0.1);
    animation->setKeyValueAt(0.15, 0.2);
    animation->setKeyValueAt(0.6, 20);
    animation->setKeyValueAt(0.7, 20);
    animation->setEndValue(20);
    animation->setDuration(2050);

    group->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("dashOffset");
    animation->setTargetObject(delegate);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    animation->setStartValue(0);
    animation->setKeyValueAt(0.15, 0);
    animation->setKeyValueAt(0.6, -7);
    animation->setKeyValueAt(0.7, -7);
    animation->setEndValue(-25);
    animation->setDuration(2050);

    group->addAnimation(animation);

    group->start();
}

CircularProgress::CircularProgress(QWidget *parent)
    : QProgressBar(parent),
      d_ptr(new CircularProgressPrivate(this))
{
    d_func()->init();
}

CircularProgress::~CircularProgress()
{
}

void CircularProgress::setProgressType(Material::ProgressType type)
{
    Q_D(CircularProgress);

    d->progressType = type;
    update();
}

Material::ProgressType CircularProgress::progressType() const
{
    Q_D(const CircularProgress);

    return d->progressType;
}


void CircularProgress::setUseThemeColors(bool state)
{
    Q_D(CircularProgress);

    d->useThemeColors = state;
    update();
}

bool CircularProgress::useThemeColors() const
{
    Q_D(const CircularProgress);

    return d->useThemeColors;
}

void CircularProgress::setLineWidth(qreal width)
{
    Q_D(CircularProgress);

    d->penWidth = width;
    update();
}

qreal CircularProgress::lineWidth() const
{
    Q_D(const CircularProgress);

    return d->penWidth;
}

void CircularProgress::setSize(int size)
{
    Q_D(CircularProgress);

    d->size = size;
    update();
}

int CircularProgress::size() const
{
    Q_D(const CircularProgress);

    return d->size;
}

void CircularProgress::setColor(const QColor &color)
{
    Q_D(CircularProgress);

    d->color = color;
    setUseThemeColors(false);
}

QColor CircularProgress::color() const
{
    Q_D(const CircularProgress);

    if (d->useThemeColors || !d->color.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->color;
    }
}

QSize CircularProgress::sizeHint() const
{
    Q_D(const CircularProgress);

    const qreal s = d->size+d->penWidth+8;
    return QSize(s, s);
}

void CircularProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(CircularProgress);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawRect(rect());

    painter.translate(width()/2, height()/2);
    painter.rotate(d->angle);

    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(d->penWidth);
    pen.setColor(color());

    if (Material::IndeterminateProgress == d->progressType)
    {
        QVector<qreal> pattern;
        pattern << d->delegate->dashLength()*d->size/50 << 30*d->size/50;

        pen.setDashOffset(d->delegate->dashOffset()*d->size/50);
        pen.setDashPattern(pattern);

        painter.setPen(pen);

        painter.drawEllipse(QPoint(0, 0), d->size/2, d->size/2);
    }
    else
    {

    }
}

void CircularProgress::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)

    Q_D(CircularProgress);

    if (++d->angle > 360) {
       d->angle -= 360;
    }
    update();
}
