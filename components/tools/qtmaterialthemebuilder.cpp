#include "qtmaterialthemebuilder.h"

#include <QDebug>
#include <QtMath>

QtMaterialTheme *QtMaterialThemeBuilder::createRandomTheme()
{
    int h = rand() % 360;
    int s = rand() % 175 + 80;
    int v = rand() % 175 + 80;
    QColor color1 = QColor::fromHsv(h, s, v);

    int h2 = (h + 50 + (rand() % 260)) % 360;
    QColor color2 = QColor::fromHsv(h2, 250, 250);

    bool dark = ((rand() % 2) == 0);

    return createThemeFromColors(color1, color2, dark);
}

QtMaterialTheme *QtMaterialThemeBuilder::createThemeFromColors(const QColor &color1, const QColor &color2, bool dark)
{
    QtMaterialTheme *theme = new QtMaterialTheme();

    theme->setColor(Material::ColorThemePrimaryMain, color1);
    theme->setColor(Material::ColorThemePrimaryDark, color1.darker());
    theme->setColor(Material::ColorThemePrimaryLight, color1.lighter());
    theme->setColor(Material::ColorThemePrimaryText, (color1.black() > 128) ? Qt::white : Qt::black);

    theme->setColor(Material::ColorThemeSecondaryMain, color2);
    theme->setColor(Material::ColorThemeSecondaryDark, color2.darker());
    theme->setColor(Material::ColorThemeSecondaryLight, color2.lighter());
    theme->setColor(Material::ColorThemeSecondaryText, (color2.black() > 128) ? Qt::white : Qt::black);

    QColor canvasColor(225, 225, 225);
    QColor textColor(50, 50, 50);
    QColor borderColor(200, 200, 200);
    if (dark)
    {
        canvasColor = QColor(50, 50, 50);
        textColor = QColor(225, 225, 225);
        borderColor = QColor(75, 75, 75);
    }
    theme->setColor(Material::ColorThemeCanvas, canvasColor);
    theme->setColor(Material::ColorThemeText, textColor);
    theme->setColor(Material::ColorThemeBorder, borderColor);

    return theme;
}

float QtMaterialThemeBuilder::colorRLuminance(const QColor &color)
{
    float r = color.redF();
    float g = color.greenF();
    float b = color.blueF();

    if (r <= 0.03928)
    {
        r /= 12.92;
    }
    else
    {
        r = powf((r + 0.055) / 1.055, 2.4);
    }

    if (g <= 0.03928)
    {
        g /= 12.92;
    }
    else
    {
        g = powf((g + 0.055) / 1.055, 2.4);
    }

    if (b <= 0.03928)
    {
        b /= 12.92;
    }
    else
    {
        b = powf((b + 0.055) / 1.055, 2.4);
    }

    return 0.2126 * r + 0.7152 * g + 0.0722 * b;
}

float QtMaterialThemeBuilder::colorContrast(const QColor &color1, const QColor &color2)
{
    float lc1 = colorRLuminance(color1);
    float lc2 = colorRLuminance(color2);

    float l1 = qMax(lc1, lc2);
    float l2 = qMin(lc1, lc2);
    return (l1 + 0.05) / (l2 + 0.05);
}

QColor QtMaterialThemeBuilder::contrastedColor(const QColor &color, const QColor &background, float minContrast)
{
    if (minContrast > 7)
    {
        minContrast = 7;
    }
    if (minContrast < 1)
    {
        minContrast = 1;
    }

    int factor = (color.lightness() < background.lightness()) ? 105 : 95;

    QColor newColor = color;
    int it = 30;
    float contrast;
    do
    {
        contrast = colorContrast(newColor, background);
        newColor = newColor.darker(factor);
        it--;
    } while (contrast < minContrast && it >= 0);
    return newColor;
}
