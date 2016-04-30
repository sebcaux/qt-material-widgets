#include <QPainter>
#include <QStyleOption>
#include "style.h"

void Style::drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w = 0) const
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
