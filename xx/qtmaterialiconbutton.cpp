#include "xx/qtmaterialiconbutton.h"
#include "xx/qtmaterialiconbutton_p.h"
#include <QPainter>
#include <QEvent>
#include "xxlib/qtmaterialstyle.h"
#include "xxlib/qtmaterialrippleoverlay.h"

/*!
 *  \class QtMaterialIconButtonPrivate
 *  \internal
 */

QtMaterialIconButtonPrivate::QtMaterialIconButtonPrivate(QtMaterialIconButton *q)
    : q_ptr(q)
{
}

QtMaterialIconButtonPrivate::~QtMaterialIconButtonPrivate()
{
}

void QtMaterialIconButtonPrivate::init()
{
    Q_Q(QtMaterialIconButton);

    rippleOverlay  = new QtMaterialRippleOverlay(q->parentWidget());
    useThemeColors = true;

    q->setStyle(&QtMaterialStyle::instance());

    QSizePolicy policy;
    policy.setWidthForHeight(true);
    q->setSizePolicy(policy);

    rippleOverlay->installEventFilter(q);
}

/*!
 *  \class QtMaterialIconButton
 */

QtMaterialIconButton::QtMaterialIconButton(const QIcon &icon, QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new QtMaterialIconButtonPrivate(this))
{
    d_func()->init();

    setIcon(icon);
}

QtMaterialIconButton::~QtMaterialIconButton()
{
}

/*!
 *  \reimp
 */
QSize QtMaterialIconButton::sizeHint() const
{
    return iconSize();
}

void QtMaterialIconButton::setUseThemeColors(bool value)
{
    Q_D(QtMaterialIconButton);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialIconButton::useThemeColors() const
{
    Q_D(const QtMaterialIconButton);

    return d->useThemeColors;
}

void QtMaterialIconButton::setColor(const QColor &color)
{
    Q_D(QtMaterialIconButton);

    d->color = color;
    update();
}

QColor QtMaterialIconButton::color() const
{
    Q_D(const QtMaterialIconButton);

    if (d->useThemeColors || !d->color.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    }
    return d->color;
}

void QtMaterialIconButton::setDisabledColor(const QColor &color)
{
    Q_D(QtMaterialIconButton);

    d->disabledColor = color;
    update();
}

QColor QtMaterialIconButton::disabledColor() const
{
    Q_D(const QtMaterialIconButton);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("disabled");
    }
    return d->disabledColor;
}

QtMaterialIconButton::QtMaterialIconButton(QtMaterialIconButtonPrivate &d, QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(&d)
{
    d_func()->init();
}

/*!
 *  \reimp
 */
bool QtMaterialIconButton::event(QEvent *event)
{
    Q_D(QtMaterialIconButton);

    switch (event->type())
    {
    case QEvent::ParentChange: {
        QWidget *widget;
        if ((widget = parentWidget())) {
            d->rippleOverlay->setParent(widget);
        }
        break;
    }
    default:
        break;
    }
    return QAbstractButton::event(event);
}

/*!
 *  \reimp
 */
bool QtMaterialIconButton::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::Resize == event->type())
    {
        Q_D(QtMaterialIconButton);

        const int s = iconSize().width()/2;
        d->rippleOverlay->setGeometry(geometry().adjusted(-s, -s, s, s));
    }
    return QAbstractButton::eventFilter(obj, event);
}

/*!
 *  \reimp
 */
void QtMaterialIconButton::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialIconButton);

    d->rippleOverlay->addRipple(QPoint(d->rippleOverlay->width(),
                                       d->rippleOverlay->height())/2,
                                iconSize().width());
    emit clicked();

    QAbstractButton::mousePressEvent(event);
}

/*!
 *  \reimp
 */
void QtMaterialIconButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QPixmap pixmap = icon().pixmap(iconSize());
    QPainter icon(&pixmap);
    icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
    icon.fillRect(pixmap.rect(), isEnabled() ? color() : disabledColor());
    painter.drawPixmap(0, 0, pixmap);
}
