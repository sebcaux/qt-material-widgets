#include "xx/qtmaterialmenuitem.h"
#include "xx/qtmaterialmenuitem_p.h"
#include <QPainter>
#include "xx/qtmaterialmenuitem_internal.h"
#include "xxlib/qtmaterialstyle.h"

/*!
 *  \class QtMaterialMenuItemPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialMenuItemPrivate::QtMaterialMenuItemPrivate(QtMaterialMenuItem *q)
    : QtMaterialFlatButtonPrivate(q)
{
}

/*!
 *  \internal
 */
QtMaterialMenuItemPrivate::~QtMaterialMenuItemPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialMenuItemPrivate::init()
{
    Q_Q(QtMaterialMenuItem);

    highlighted  = false;

    QFont font(q->font());
    font.setCapitalization(QFont::MixedCase);
    font.setPointSize(11);
    font.setStyleName("Regular");
    q->setFont(font);

    q->setOverlayStyle(XXMaterial::GrayOverlay);
    q->setForegroundColor(QtMaterialStyle::instance().themeColor("text"));
    q->setCornerRadius(0);
}

/*!
 *  \class QtMaterialMenuItem
 */

QtMaterialMenuItem::QtMaterialMenuItem(QWidget *parent)
    : QtMaterialFlatButton(*new QtMaterialMenuItemPrivate(this), parent)
{
    d_func()->init();
}

QtMaterialMenuItem::~QtMaterialMenuItem()
{
}

void QtMaterialMenuItem::setHighlighted(bool value)
{
    Q_D(QtMaterialMenuItem);

    d->highlighted = value;
}

bool QtMaterialMenuItem::isHighlighted() const
{
    Q_D(const QtMaterialMenuItem);

    return d->highlighted;
}

void QtMaterialMenuItem::paintForeground(QPainter *painter)
{
    if (isEnabled()) {
        painter->setPen(foregroundColor());
    } else {
        painter->setPen(disabledForegroundColor());
    }

    QRect r(rect());

    if (icon().isNull())  {
        painter->drawText(r.marginsRemoved(QMargins(14, 0, 14, 0)),
                          Qt::AlignVCenter | Qt::AlignLeft,
                          text());
        return;
    }

    QSize textSize(fontMetrics().size(Qt::TextSingleLine, text()));
    QSize base(size()-textSize);

    const int iw = iconSize().width() + IconPadding;

    QRect textGeometry(QPoint(14, base.height()/2), textSize);
    QRect iconGeometry(QPoint(14, (height()-iconSize().height())/2), iconSize());

    if (XXMaterial::LeftIcon == iconPlacement()) {
        textGeometry.translate(iw, 0);
    } else {
        iconGeometry.translate(textSize.width() + IconPadding, 0);
    }

    painter->drawText(textGeometry,
                      Qt::AlignVCenter | Qt::AlignLeft,
                      text());

    QPixmap pixmap = icon().pixmap(iconSize());
    QPainter icon(&pixmap);
    icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
    icon.fillRect(pixmap.rect(), painter->pen().color());
    painter->drawPixmap(iconGeometry, pixmap);
}
