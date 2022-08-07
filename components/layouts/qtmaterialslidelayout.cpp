#include "qtmaterialslidelayout.h"

#include "qtmaterialslidelayout_p.h"

#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QWidget>

/*!
 *  \class QtMaterialSlideLayoutPrivate
 *  \internal
 */

QtMaterialSlideLayoutPrivate::QtMaterialSlideLayoutPrivate(QtMaterialSlideLayout *q)
    : q_ptr(q)
{
}

QtMaterialSlideLayoutPrivate::~QtMaterialSlideLayoutPrivate()
{
}

void QtMaterialSlideLayoutPrivate::init()
{
    Q_Q(QtMaterialSlideLayout);

    prevWidgetAnimation = new QPropertyAnimation(q);
    newWidgetAnimation = new QPropertyAnimation(q);
    prevWidgetAnimation->setPropertyName("pos");
    newWidgetAnimation->setPropertyName("pos");

    animationGroup = new QParallelAnimationGroup(q);
    animationGroup->addAnimation(prevWidgetAnimation);
    animationGroup->addAnimation(newWidgetAnimation);
    QObject::connect(prevWidgetAnimation,
                     &QPropertyAnimation::finished,
                     q,
                     [=]
                     {
                         if (prevWidget != nullptr && newWidget != nullptr)
                         {
                             prevWidget->hide();
                             q->setCurrentWidget(newWidget);
                             prevWidget = nullptr;
                             newWidget = nullptr;
                         }
                     });

    prevWidget = nullptr;
    newWidget = nullptr;

    animationDuration = 700;
    animationType = QEasingCurve::OutBack;
    orientation = Qt::Horizontal;
}

/*!
 *  \class QtMaterialSlideLayout
 */

QtMaterialSlideLayout::QtMaterialSlideLayout(QWidget *parent)
    : QStackedLayout(parent),
      d_ptr(new QtMaterialSlideLayoutPrivate(this))
{
    d_func()->init();
}

QtMaterialSlideLayout::QtMaterialSlideLayout(QLayout *parentLayout)
    : QStackedLayout(parentLayout),
      d_ptr(new QtMaterialSlideLayoutPrivate(this))
{
    d_func()->init();
}

QtMaterialSlideLayout::~QtMaterialSlideLayout()
{
}

void QtMaterialSlideLayout::slideToIndex(int index)
{
    QWidget *w = widget(index);
    slideToWidget(w);
}

void QtMaterialSlideLayout::slideToWidget(QWidget *widget)
{
    Q_D(QtMaterialSlideLayout);

    if (widget == nullptr || parentWidget() == nullptr)
    {
        return;
    }

    if (d->animationGroup->state() == QAbstractAnimation::Running)
    {
        if (widget == d->newWidget)
        {
            return;
        }
        // TODO improve this transition
        d->animationGroup->setCurrentTime(d->animationGroup->duration());
        d->animationGroup->stop();
        if (d->newWidget != nullptr)
        {
            setCurrentWidget(d->newWidget);
        }
    }
    if (widget == currentWidget())
    {
        return;
    }

    d->prevWidget = currentWidget();
    d->newWidget = widget;

    const QRect &geometry = parentWidget()->geometry();

    d->direction = 1;
    if (indexOf(d->prevWidget) > indexOf(d->newWidget))
    {
        d->direction = -1;
    }

    d->prevWidgetAnimation->setTargetObject(d->prevWidget);
    d->prevWidgetAnimation->setEasingCurve(d->animationType);
    d->prevWidgetAnimation->setDuration(d->animationDuration);
    d->prevWidgetAnimation->setStartValue(QPoint(0, 0));
    d->prevWidgetAnimation->setEndValue(QPoint(-d->direction * geometry.width(), 0));

    d->newWidgetAnimation->setTargetObject(d->newWidget);
    d->newWidgetAnimation->setEasingCurve(d->animationType);
    d->newWidgetAnimation->setDuration(d->animationDuration);
    d->newWidgetAnimation->setStartValue(QPoint(d->direction * geometry.width(), 0));
    d->newWidgetAnimation->setEndValue(QPoint(0, 0));

    d->animationGroup->start();
    d->newWidget->raise();
    d->newWidget->show();
    d->newWidget->setGeometry(geometry.width(), 0, geometry.width(), geometry.height());
}

Qt::Orientation QtMaterialSlideLayout::orientation() const
{
    Q_D(const QtMaterialSlideLayout);

    return d->orientation;
}

void QtMaterialSlideLayout::setOrientation(Qt::Orientation orientation)
{
    Q_D(QtMaterialSlideLayout);

    d->orientation = orientation;
}

QEasingCurve::Type QtMaterialSlideLayout::animationType() const
{
    Q_D(const QtMaterialSlideLayout);

    return d->animationType;
}

void QtMaterialSlideLayout::setAnimationType(const QEasingCurve::Type animationType)
{
    Q_D(QtMaterialSlideLayout);

    d->animationType = animationType;
}

uint QtMaterialSlideLayout::animationDuration() const
{
    Q_D(const QtMaterialSlideLayout);

    return d->animationDuration;
}

void QtMaterialSlideLayout::setAnimationDuration(uint animationDuration)
{
    Q_D(QtMaterialSlideLayout);

    d->animationDuration = animationDuration;
}

void QtMaterialSlideLayout::setGeometry(const QRect &rect)
{
    Q_D(QtMaterialSlideLayout);

    if (d->animationGroup->state() == QAbstractAnimation::Running)
    {
        d->prevWidgetAnimation->setEndValue(QPoint(-d->direction * rect.width(), 0));
        d->newWidgetAnimation->setStartValue(QPoint(d->direction * rect.width(), 0));
        d->newWidget->resize(rect.size());
    }
    else
    {
        if (QWidget *widget = currentWidget())
        {
            widget->setGeometry(rect);
        }
    }
}
