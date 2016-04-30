#include <QPainter>
#include <QStyleOption>
#include "lib/style.h"

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
