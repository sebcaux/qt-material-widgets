#include "qtmaterialflatbutton.h"

#include "lib/qtmaterialripple.h"
#include "lib/qtmaterialrippleoverlay.h"
#include "lib/qtmaterialstyle.h"
#include "qtmaterialflatbutton_internal.h"
#include "qtmaterialflatbutton_p.h"

#include <QBitmap>
#include <QEventTransition>
#include <QGraphicsDropShadowEffect>
#include <QIcon>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>

/*!
 *  \class QtMaterialFlatButtonPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialFlatButtonPrivate::QtMaterialFlatButtonPrivate(QtMaterialFlatButton *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialFlatButtonPrivate::~QtMaterialFlatButtonPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialFlatButtonPrivate::init()
{
    Q_Q(QtMaterialFlatButton);

    role = Material::Default;
    type = Material::ButtonText;
    rippleStyle = Material::PositionedRipple;
    iconPlacement = Material::LeftIcon;
    overlayStyle = Material::NoOverlay;
    textAlignment = Qt::AlignHCenter;
    fixedRippleRadius = 64;
    cornerRadius = 3;
    baseOpacity = 0.13;
    useThemeColors = true;
    useFixedRippleRadius = false;
    haloVisible = false;

    q->setStyle(&QtMaterialStyle::instance());
    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);

    q->setFont(QtMaterialStyle::instance().themeFont(Material::FontButton));

    QPainterPath path;
    path.addRoundedRect(q->rect(), cornerRadius, cornerRadius);
    rippleOverlay = new QtMaterialRippleOverlay(q);
    rippleOverlay->setClipPath(path);
    rippleOverlay->setClipping(true);

    stateMachine = new QtMaterialFlatButtonStateMachine(q);
    stateMachine->setupProperties();
    stateMachine->startAnimations();

    shadowEffect = nullptr;
    shadowStateMachine = nullptr;
}

/*!
 *  \internal
 */
void QtMaterialFlatButtonPrivate::initRaiseEffect()
{
    Q_Q(QtMaterialFlatButton);

    shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setBlurRadius(7);
    shadowEffect->setOffset(QPointF(0, 2));
    shadowEffect->setColor(QColor(0, 0, 0, 75));
    if (!q->isEnabled())
    {
        shadowEffect->setEnabled(false);
    }
    q->setGraphicsEffect(shadowEffect);

    q->setMinimumHeight(42);
    q->setBaseOpacity(0.3);

    shadowStateMachine = new QStateMachine(q);

    shadowNormalState = new QState;
    shadowNormalState->assignProperty(shadowEffect, "offset", QPointF(0, 2));
    shadowNormalState->assignProperty(shadowEffect, "blurRadius", 7);
    shadowStateMachine->addState(shadowNormalState);

    shadowPressedState = new QState;
    shadowPressedState->assignProperty(shadowEffect, "offset", QPointF(0, 5));
    shadowPressedState->assignProperty(shadowEffect, "blurRadius", 29);
    shadowStateMachine->addState(shadowPressedState);

    QAbstractTransition *transition;

    transition = new QEventTransition(q, QEvent::MouseButtonPress);
    transition->setTargetState(shadowPressedState);
    shadowNormalState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::MouseButtonDblClick);
    transition->setTargetState(shadowPressedState);
    shadowNormalState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::MouseButtonRelease);
    transition->setTargetState(shadowNormalState);
    shadowPressedState->addTransition(transition);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(shadowEffect, "offset", q);
    animation->setDuration(100);
    shadowStateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(shadowEffect, "blurRadius", q);
    animation->setDuration(100);
    shadowStateMachine->addDefaultAnimation(animation);

    shadowStateMachine->setInitialState(shadowNormalState);
    shadowStateMachine->start();
}

void QtMaterialFlatButtonPrivate::removeRaiseEffect()
{
    Q_Q(QtMaterialFlatButton);

    q->setGraphicsEffect(nullptr);
    delete shadowStateMachine;
    shadowEffect = nullptr;
    shadowStateMachine = nullptr;
}

bool QtMaterialFlatButtonPrivate::isTranparent() const
{
    if (type == Material::ButtonText || type == Material::ButtonOutlined)
    {
        return true;
    }
    return false;
}

/*!
 *  \class QtMaterialFlatButton
 */

QtMaterialFlatButton::QtMaterialFlatButton(QWidget *parent)
    : QPushButton(parent),
      d_ptr(new QtMaterialFlatButtonPrivate(this))
{
    d_func()->init();

    applyPreset(Material::ButtonTextDefault);
}

QtMaterialFlatButton::QtMaterialFlatButton(const QString &text, Material::ButtonPreset preset, QWidget *parent)
    : QPushButton(text, parent),
      d_ptr(new QtMaterialFlatButtonPrivate(this))
{
    d_func()->init();

    applyPreset(preset);
}

QtMaterialFlatButton::QtMaterialFlatButton(const QIcon &icon, const QString &text, Material::ButtonPreset preset, QWidget *parent)
    : QPushButton(text, parent),
      d_ptr(new QtMaterialFlatButtonPrivate(this))
{
    d_func()->init();

    applyPreset(preset);
    setIcon(icon);
}

QtMaterialFlatButton::~QtMaterialFlatButton()
{
}

void QtMaterialFlatButton::applyPreset(Material::ButtonPreset preset)
{
    switch (preset)
    {
        case Material::ButtonTextDefault:
        case Material::ButtonTextPrimary:
        case Material::ButtonTextSecondary:
            setType(Material::ButtonText);
            break;

        case Material::ButtonOutlinedDefault:
        case Material::ButtonOutlinedPrimary:
        case Material::ButtonOutlinedSecondary:
            setType(Material::ButtonOutlined);
            break;

        case Material::ButtonRaisedDefault:
        case Material::ButtonRaisedPrimary:
        case Material::ButtonRaisedSecondary:
            setType(Material::ButtonRaised);
            break;

        case Material::ButtonFlatDefault:
        case Material::ButtonFlatPrimary:
        case Material::ButtonFlatSecondary:
            setType(Material::ButtonFlat);
            break;
    }
    switch (preset)
    {
        case Material::ButtonTextDefault:
        case Material::ButtonOutlinedDefault:
        case Material::ButtonRaisedDefault:
        case Material::ButtonFlatDefault:
            setRole(Material::Default);
            break;

        case Material::ButtonTextPrimary:
        case Material::ButtonOutlinedPrimary:
        case Material::ButtonRaisedPrimary:
        case Material::ButtonFlatPrimary:
            setRole(Material::Primary);
            break;

        case Material::ButtonTextSecondary:
        case Material::ButtonOutlinedSecondary:
        case Material::ButtonRaisedSecondary:
        case Material::ButtonFlatSecondary:
            setRole(Material::Secondary);
            break;
    }
}

void QtMaterialFlatButton::setUseThemeColors(bool value)
{
    Q_D(QtMaterialFlatButton);

    if (d->useThemeColors == value)
    {
        return;
    }

    d->useThemeColors = value;
    d->stateMachine->setupProperties();
}

bool QtMaterialFlatButton::useThemeColors() const
{
    Q_D(const QtMaterialFlatButton);

    return d->useThemeColors;
}

void QtMaterialFlatButton::setRole(Material::Role role)
{
    Q_D(QtMaterialFlatButton);

    d->role = role;
    d->stateMachine->setupProperties();
}

Material::Role QtMaterialFlatButton::role() const
{
    Q_D(const QtMaterialFlatButton);

    return d->role;
}

void QtMaterialFlatButton::setType(Material::ButtonType type)
{
    Q_D(QtMaterialFlatButton);

    if (type == d->type)
    {
        return;
    }
    if (type == Material::ButtonRaised)
    {
        d->initRaiseEffect();
    }
    else
    {
        d->removeRaiseEffect();
    }

    d->type = type;
    d->stateMachine->setupProperties();
}

Material::ButtonType QtMaterialFlatButton::type() const
{
    Q_D(const QtMaterialFlatButton);

    return d->type;
}

void QtMaterialFlatButton::setForegroundColor(const QColor &color)
{
    Q_D(QtMaterialFlatButton);

    d->foregroundColor = color;

    d->useThemeColors = false;
    update();
}

QColor QtMaterialFlatButton::foregroundColor() const
{
    Q_D(const QtMaterialFlatButton);

    if (d->useThemeColors || !d->foregroundColor.isValid())
    {
        if (!d->isTranparent())
        {
            return QtMaterialStyle::instance().themeColor(Material::ColorThemeCanvas);
        }
        switch (d->role)
        {
            case Material::Primary:
                return QtMaterialStyle::instance().themeColor(Material::ColorThemePrimaryMain);

            case Material::Secondary:
                return QtMaterialStyle::instance().themeColor(Material::ColorThemeSecondaryMain);

            case Material::Default:
            default:
                return QtMaterialStyle::instance().themeColor(Material::ColorThemeText);
        }
    }
    return d->foregroundColor;
}

void QtMaterialFlatButton::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialFlatButton);

    d->backgroundColor = color;

    d->useThemeColors = false;
    update();
}

QColor QtMaterialFlatButton::backgroundColor() const
{
    Q_D(const QtMaterialFlatButton);

    if (d->useThemeColors || !d->backgroundColor.isValid())
    {
        switch (d->role)
        {
            case Material::Primary:
                return QtMaterialStyle::instance().themeColor(Material::ColorThemePrimaryMain);

            case Material::Secondary:
                return QtMaterialStyle::instance().themeColor(Material::ColorThemeSecondaryMain);

            case Material::Default:
            default:
                return QtMaterialStyle::instance().themeColor(Material::ColorThemeText);
        }
    }
    return d->backgroundColor;
}

void QtMaterialFlatButton::setOverlayColor(const QColor &color)
{
    Q_D(QtMaterialFlatButton);

    d->overlayColor = color;

    d->useThemeColors = false;

    setOverlayStyle(Material::TintedOverlay);
    update();
}

QColor QtMaterialFlatButton::overlayColor() const
{
    Q_D(const QtMaterialFlatButton);

    if (d->useThemeColors || !d->overlayColor.isValid())
    {
        return foregroundColor();
    }
    return d->overlayColor;
}

void QtMaterialFlatButton::setDisabledForegroundColor(const QColor &color)
{
    Q_D(QtMaterialFlatButton);

    d->disabledColor = color;

    d->useThemeColors = false;
    update();
}

QColor QtMaterialFlatButton::disabledForegroundColor() const
{
    Q_D(const QtMaterialFlatButton);

    if (d->useThemeColors || !d->disabledColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeDisabled1);
    }

    return d->disabledColor;
}

void QtMaterialFlatButton::setDisabledBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialFlatButton);

    d->disabledBackgroundColor = color;

    d->useThemeColors = false;
    update();
}

QColor QtMaterialFlatButton::disabledBackgroundColor() const
{
    Q_D(const QtMaterialFlatButton);

    if (d->useThemeColors || !d->disabledBackgroundColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeDisabled3);
    }

    return d->disabledBackgroundColor;
}

void QtMaterialFlatButton::setFontSize(qreal size)
{
    Q_D(QtMaterialFlatButton);

    d->fontSize = size;

    QFont f(font());
    f.setPointSizeF(size);
    setFont(f);

    updateGeometry();
    update();
}

qreal QtMaterialFlatButton::fontSize() const
{
    return font().pointSize();
}

void QtMaterialFlatButton::setHaloVisible(bool visible)
{
    Q_D(QtMaterialFlatButton);

    d->haloVisible = visible;
    update();
}

bool QtMaterialFlatButton::isHaloVisible() const
{
    Q_D(const QtMaterialFlatButton);

    return d->haloVisible;
}

void QtMaterialFlatButton::setOverlayStyle(Material::OverlayStyle style)
{
    Q_D(QtMaterialFlatButton);

    d->overlayStyle = style;
    update();
}

Material::OverlayStyle QtMaterialFlatButton::overlayStyle() const
{
    Q_D(const QtMaterialFlatButton);

    return d->overlayStyle;
}

void QtMaterialFlatButton::setRippleStyle(Material::RippleStyle style)
{
    Q_D(QtMaterialFlatButton);

    d->rippleStyle = style;
}

Material::RippleStyle QtMaterialFlatButton::rippleStyle() const
{
    Q_D(const QtMaterialFlatButton);

    return d->rippleStyle;
}

void QtMaterialFlatButton::setIconPlacement(Material::ButtonIconPlacement placement)
{
    Q_D(QtMaterialFlatButton);

    d->iconPlacement = placement;
    update();
}

Material::ButtonIconPlacement QtMaterialFlatButton::iconPlacement() const
{
    Q_D(const QtMaterialFlatButton);

    return d->iconPlacement;
}

void QtMaterialFlatButton::setCornerRadius(qreal radius)
{
    Q_D(QtMaterialFlatButton);

    d->cornerRadius = radius;
    updateClipPath();
    update();
}

qreal QtMaterialFlatButton::cornerRadius() const
{
    Q_D(const QtMaterialFlatButton);

    return d->cornerRadius;
}

void QtMaterialFlatButton::setBaseOpacity(qreal opacity)
{
    Q_D(QtMaterialFlatButton);

    d->baseOpacity = opacity;
    d->stateMachine->setupProperties();
}

qreal QtMaterialFlatButton::baseOpacity() const
{
    Q_D(const QtMaterialFlatButton);

    return d->baseOpacity;
}

void QtMaterialFlatButton::setCheckable(bool value)
{
    Q_D(QtMaterialFlatButton);

    d->stateMachine->updateCheckedStatus();

    QPushButton::setCheckable(value);
}

void QtMaterialFlatButton::setHasFixedRippleRadius(bool value)
{
    Q_D(QtMaterialFlatButton);

    d->useFixedRippleRadius = value;
}

bool QtMaterialFlatButton::hasFixedRippleRadius() const
{
    Q_D(const QtMaterialFlatButton);

    return d->useFixedRippleRadius;
}

void QtMaterialFlatButton::setFixedRippleRadius(qreal radius)
{
    Q_D(QtMaterialFlatButton);

    d->fixedRippleRadius = radius;
    setHasFixedRippleRadius(true);
}

void QtMaterialFlatButton::setTextAlignment(Qt::Alignment alignment)
{
    Q_D(QtMaterialFlatButton);

    d->textAlignment = alignment;
}

Qt::Alignment QtMaterialFlatButton::textAlignment() const
{
    Q_D(const QtMaterialFlatButton);

    return d->textAlignment;
}

/*!
 *  \reimp
 */
QSize QtMaterialFlatButton::sizeHint() const
{
    ensurePolished();

    QSize labelSize(fontMetrics().size(Qt::TextSingleLine, text()));

    int w = labelSize.width() + 20;
    int h = labelSize.height();
    if (!icon().isNull())
    {
        w += iconSize().width() + QtMaterialFlatButton::IconPadding;
        h = qMax(h, iconSize().height());
    }
    return QSize(w, h + 20);
}

QtMaterialFlatButton::QtMaterialFlatButton(QtMaterialFlatButtonPrivate &d, QWidget *parent, Material::ButtonPreset preset)
    : QPushButton(parent),
      d_ptr(&d)
{
    d_func()->init();

    applyPreset(preset);
}

/*!
 *  \reimp
 */
void QtMaterialFlatButton::checkStateSet()
{
    Q_D(QtMaterialFlatButton);

    d->stateMachine->updateCheckedStatus();

    QPushButton::checkStateSet();
}

/*!
 *  \reimp
 */
bool QtMaterialFlatButton::event(QEvent *event)
{
    Q_D(QtMaterialFlatButton);

    if (d->shadowStateMachine != nullptr && d->shadowEffect != nullptr)
    {
        if (QEvent::EnabledChange == event->type())
        {
            if (isEnabled())
            {
                /*if (!d->shadowStateMachine->isRunning())
                {
                    d->shadowStateMachine->start();
                }*/
                d->shadowEffect->setEnabled(true);
            }
            else
            {
                //d->shadowStateMachine->stop();
                d->shadowEffect->setEnabled(false);
            }
        }
    }
    return QPushButton::event(event);
}

/*!
 *  \reimp
 */
void QtMaterialFlatButton::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialFlatButton);

    if (d->rippleStyle != Material::NoRipple)
    {
        QPoint pos;
        qreal radiusEndValue;

        if (d->rippleStyle == Material::CenteredRipple)
        {
            pos = rect().center();
        }
        else
        {
            pos = event->pos();
        }

        if (d->useFixedRippleRadius)
        {
            radiusEndValue = d->fixedRippleRadius;
        }
        else
        {
            radiusEndValue = static_cast<qreal>(width()) / 2;
        }

        QtMaterialRipple *ripple = new QtMaterialRipple(pos);

        ripple->setRadiusEndValue(radiusEndValue);
        ripple->setOpacityStartValue(0.35);
        ripple->setColor(foregroundColor());
        ripple->radiusAnimation()->setDuration(600);
        ripple->opacityAnimation()->setDuration(1300);

        d->rippleOverlay->addRipple(ripple);
    }

    QPushButton::mousePressEvent(event);
}

/*!
 *  \reimp
 */
void QtMaterialFlatButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(QtMaterialFlatButton);

    QPushButton::mouseReleaseEvent(event);

    d->stateMachine->updateCheckedStatus();
}

/*!
 *  \reimp
 */
void QtMaterialFlatButton::resizeEvent(QResizeEvent *event)
{
    QPushButton::resizeEvent(event);

    updateClipPath();
}

/*!
 *  \reimp
 */
void QtMaterialFlatButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialFlatButton);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const qreal cr = d->cornerRadius;

    if (cr > 0)
    {
        QPainterPath path;
        path.addRoundedRect(rect(), cr, cr);

        painter.setClipPath(path);
        painter.setClipping(true);
    }

    paintBackground(&painter);

    if (d->haloVisible)
    {
        paintHalo(&painter);
    }

    painter.setOpacity(1);
    painter.setClipping(false);

    paintForeground(&painter);
}

/*!
 *  \internal
 */
void QtMaterialFlatButton::paintBackground(QPainter *painter)
{
    Q_D(QtMaterialFlatButton);

    const qreal overlayOpacity = d->stateMachine->overlayOpacity();
    const qreal checkedProgress = d->stateMachine->checkedOverlayProgress();

    if (!d->isTranparent())
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        if (isEnabled())
        {
            brush.setColor(backgroundColor());
        }
        else
        {
            brush.setColor(disabledBackgroundColor());
        }
        painter->setOpacity(1);
        painter->setBrush(brush);
        painter->setPen(Qt::NoPen);
        painter->drawRect(rect());
    }

    if (!isEnabled())
    {
        return;
    }

    painter->setPen(Qt::NoPen);

    if ((d->overlayStyle != Material::NoOverlay) && (overlayOpacity > 0))
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        if (d->overlayStyle == Material::TintedOverlay)
        {
            brush.setColor(overlayColor());
        }
        else
        {
            brush.setColor(Qt::gray);
        }
        painter->setOpacity(overlayOpacity);
        painter->setBrush(brush);
        painter->drawRect(rect());
    }

    if (isCheckable() && checkedProgress > 0)
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        const qreal q = (d->isTranparent()) ? 0.45 : 0.7;
        brush.setColor(foregroundColor());
        painter->setOpacity(q * checkedProgress);
        painter->setBrush(brush);
        QRect r(rect());
        r.setHeight(static_cast<qreal>(r.height()) * checkedProgress);
        painter->drawRect(r);
    }
}

/*!
 *  \internal
 */
void QtMaterialFlatButton::paintHalo(QPainter *painter)
{
    Q_D(QtMaterialFlatButton);

    const qreal opacity = d->stateMachine->haloOpacity();
    const qreal s = d->stateMachine->haloScaleFactor() * d->stateMachine->haloSize();
    const qreal radius = static_cast<qreal>(width()) * s;

    if (isEnabled() && opacity > 0)
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(foregroundColor());
        painter->setOpacity(opacity);
        painter->setBrush(brush);
        painter->setPen(Qt::NoPen);
        const QPointF center = rect().center();
        painter->drawEllipse(center, radius, radius);
    }
}

#define COLOR_INTERPOLATE(CH) (1 - progress) * source.CH() + progress *dest.CH()

/*!
 *  \internal
 */
void QtMaterialFlatButton::paintForeground(QPainter *painter)
{
    Q_D(QtMaterialFlatButton);

    if (isEnabled())
    {
        painter->setPen(foregroundColor());
        const qreal progress = d->stateMachine->checkedOverlayProgress();
        if (isCheckable() && progress > 0)
        {
            QColor source = foregroundColor();
            QColor dest = (d->isTranparent()) ? Qt::white : backgroundColor();
            if (qFuzzyCompare(1, progress))
            {
                painter->setPen(dest);
            }
            else
            {
                painter->setPen(QColor(COLOR_INTERPOLATE(red), COLOR_INTERPOLATE(green), COLOR_INTERPOLATE(blue), COLOR_INTERPOLATE(alpha)));
            }
        }
    }
    else
    {
        painter->setPen(disabledForegroundColor());
    }

    if (d->type == Material::ButtonOutlined)
    {
        painter->setBrush(Qt::NoBrush);
        painter->drawPath(painter->clipPath());
    }

    if (icon().isNull())
    {
        if (d->textAlignment == Qt::AlignLeft)
        {
            painter->drawText(rect().adjusted(TextPadding, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text());
        }
        else
        {
            painter->drawText(rect(), Qt::AlignHCenter | Qt::AlignVCenter, text());
        }
        return;
    }

    QSize iconSize(this->iconSize());
    QSize textSize(fontMetrics().size(Qt::TextSingleLine, text()));
    QSize base(size() - textSize);

    const int iw = iconSize.width() + IconPadding;
    QPoint pos((d->textAlignment == Qt::AlignLeft) ? TextPadding : (base.width() - iw) / 2, 0);

    QRect textGeometry(pos + QPoint(0, base.height() / 2), textSize);
    QRect iconGeometry(pos + QPoint(0, (height() - iconSize.height()) / 2), iconSize);

    if (d->iconPlacement == Material::LeftIcon)
    {
        textGeometry.translate(iw, 0);
    }
    else
    {
        iconGeometry.translate(textSize.width() + IconPadding, 0);
    }

    painter->drawText(textGeometry, Qt::AlignHCenter | Qt::AlignVCenter, text());

    QPixmap pixmap = icon().pixmap(iconSize);
    QPainter icon(&pixmap);
    icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
    icon.fillRect(pixmap.rect(), painter->pen().color());
    painter->drawPixmap(iconGeometry, pixmap);
}

/*!
 *  \internal
 */
void QtMaterialFlatButton::updateClipPath()
{
    Q_D(QtMaterialFlatButton);

    const qreal radius = d->cornerRadius;

    QPainterPath path;
    path.addRoundedRect(rect(), radius, radius);
    d->rippleOverlay->setClipPath(path);
}
