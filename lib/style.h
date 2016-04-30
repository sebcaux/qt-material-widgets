#ifndef STYLE_H
#define STYLE_H

#include <QCommonStyle>

class Style : public QCommonStyle
{
    Q_OBJECT

public:
    static Style &instance()
    {
        static Style instance;
        return instance;
    }

    void drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p,
                       const QWidget *w = 0) const Q_DECL_OVERRIDE;

private:
    Style() {}

    Style(Style const &);
    void operator=(Style const &);
};

#endif // STYLE_H
