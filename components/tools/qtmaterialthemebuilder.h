#ifndef QTMATERIALTHEMEBUILDER_H
#define QTMATERIALTHEMEBUILDER_H

#include "lib/qtmaterialtheme.h"

#include <QColor>

class QtMaterialThemeBuilder
{
public:
    static QtMaterialTheme *createRandomTheme();
    static QtMaterialTheme *createThemeFromColors(const QColor &color1, const QColor &color2, bool dark = false);

    static float colorRLuminance(const QColor &color);
    static float colorContrast(const QColor &color1, const QColor &color2);
    static QColor contrastedColor(const QColor &color, const QColor &background, float minContrast);
};

#endif  // QTMATERIALTHEMEBUILDER_H
