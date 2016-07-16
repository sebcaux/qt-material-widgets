#include "xxlib/qtmaterialcheckable.h"
#include "xxlib/qtmaterialcheckable_p.h"
#include <QPainter>
#include <QFontDatabase>
#include <QEvent>
#include "xxlib/qtmaterialrippleoverlay.h"
#include "xxlib/qtmaterialripple.h"
#include "xxlib/qtmaterialstyle.h"
#include "xxlib/qtmaterialcheckable_internal.h"

/*!
 *  \class QtMaterialCheckablePrivate
 *  \internal
 */

QtMaterialCheckablePrivate::QtMaterialCheckablePrivate(QtMaterialCheckable *q)
    : q_ptr(q)
{
}

QtMaterialCheckablePrivate::~QtMaterialCheckablePrivate()
{
}

void QtMaterialCheckablePrivate::init()
{
    Q_Q(QtMaterialCheckable);

    rippleOverlay = new QtMaterialRippleOverlay;
    checkedIcon   = new QtMaterialCheckableIcon(QIcon("../qt-material-widgets/ic_check_box_black_24px.svg"));
    uncheckedIcon = new QtMaterialCheckableIcon(QIcon("../qt-material-widgets/ic_check_box_outline_blank_black_24px.svg"));

    rippleOverlay->setParent(q->parentWidget());
    rippleOverlay->installEventFilter(q);

    q->setCheckable(true);
    q->setStyle(&QtMaterialStyle::instance());

    QFontDatabase db;
    QFont font(db.font("Roboto", "Medium", 11));
    q->setFont(font);
}

/*!
 *  \class QtMaterialCheckable
 */

QtMaterialCheckable::QtMaterialCheckable(QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new QtMaterialCheckablePrivate(this))
{
    d_func()->init();
}

QtMaterialCheckable::~QtMaterialCheckable()
{
}

QSize QtMaterialCheckable::sizeHint() const
{
    if (text().isEmpty()) {
        return QSize(40, 40);
    }
    return QSize(fontMetrics().size(Qt::TextShowMnemonic, text()).width()+52, 40);
}

QtMaterialCheckable::QtMaterialCheckable(QtMaterialCheckablePrivate &d, QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(&d)
{
    d_func()->init();
}

bool QtMaterialCheckable::event(QEvent *event)
{
    Q_D(QtMaterialCheckable);

    switch (event->type())
    {
    case QEvent::ParentChange:
        QWidget *widget;
        if ((widget = parentWidget())) {
            d->rippleOverlay->setParent(widget);
        }
        break;
    default:
        break;
    }
    return QAbstractButton::event(event);
}

bool QtMaterialCheckable::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::Resize == event->type())
    {
        Q_D(QtMaterialCheckable);

        d->rippleOverlay->setGeometry(geometry().adjusted(-8, -8, 8, 8));
    }
    return QAbstractButton::eventFilter(obj, event);
}

void QtMaterialCheckable::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialCheckable);

    if (!isEnabled()) {
        return;
    }

    QtMaterialRipple *ripple = new QtMaterialRipple(QPoint(28, 28));
    ripple->setRadiusEndValue(22);
    //ripple->setColor(isChecked() ? checkedColor() : uncheckedColor());
    if (isChecked()) {
        ripple->setOpacityStartValue(1);
    }
    d->rippleOverlay->addRipple(ripple);

    QAbstractButton::mousePressEvent(event);
}

void QtMaterialCheckable::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.drawRect(rect().adjusted(0, 0, -1, -1));
}
