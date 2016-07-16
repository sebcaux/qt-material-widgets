#include "menuitemplus.h"
#include <QPainter>

MenuItemPlus::MenuItemPlus(QWidget *parent)
    : QtMaterialFlatButton(parent)
{
    setHaloVisible(false);

    QFont f(font());
    f.setCapitalization(QFont::MixedCase);
    f.setPointSize(11);
    f.setStyleName("Regular");
    setFont(f);

    setOverlayStyle(XXMaterial::TintedOverlay);
    setCornerRadius(0);
}

MenuItemPlus::~MenuItemPlus()
{
}

void MenuItemPlus::paintForeground(QPainter *painter)
{
    painter->setPen(foregroundColor());

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
