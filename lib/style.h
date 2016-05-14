#ifndef STYLE_H
#define STYLE_H

#include <QCommonStyle>
#include "theme.h"

class Style : public QCommonStyle
{
    Q_OBJECT

public:
    static Style &instance()
    {
        static Style instance;
        instance.setTheme(new Theme);
        return instance;
    }

    void setTheme(Theme *theme);
    QColor themeColor(const QString &key) const;

    void drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p,
                       const QWidget *w = 0) const Q_DECL_OVERRIDE;

    int pixelMetric(PixelMetric m, const QStyleOption *opt,
                    const QWidget *widget) const Q_DECL_OVERRIDE;

private:
    Style() {}

    Style(Style const &);
    void operator=(Style const &);

    Theme *_theme;
};

#endif // STYLE_H
