#include "lib/style.h"
#include <QPainter>
#include <QStyleOption>

void Style::setTheme(Theme *theme)
{
    _theme = theme;
    theme->setParent(this);
}

QColor Style::themeColor(const QString &key) const
{
    if (!_theme)
        return QColor();

    return _theme->getColor(key);
}

void Style::drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w) const
{
    switch (pe)
    {
    case PE_FrameFocusRect:
        //p->setPen(Qt::blue);
        //p->drawRect(opt->rect);
        break;
    default:
        QCommonStyle::drawPrimitive(pe, opt, p, w);
    }
}

int Style::pixelMetric(PixelMetric m, const QStyleOption *opt, const QWidget *widget) const
{
    switch (m)
    {
    case PM_ButtonShiftHorizontal:
    case PM_ButtonShiftVertical:
        return 0;
    default:
        break;
    }
    return QCommonStyle::pixelMetric(m, opt, widget);
}
