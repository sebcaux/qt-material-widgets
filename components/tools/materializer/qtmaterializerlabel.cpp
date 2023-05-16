#include "qtmaterializerlabel.h"

#include "lib/qtmaterialstyle.h"

#include <qcoreevent.h>

#include <QLabel>

QtMaterializerLabel::QtMaterializerLabel(QLabel *parent)
    : QObject(parent),
      _label(parent)
{
    updateColors();
    updateFont();

    _label->installEventFilter(this);
}

void QtMaterializerLabel::updateColors()
{
    QPalette p = _label->palette();
    p.setColor(QPalette::WindowText, QtMaterialStyle::instance().themeColor(Material::ColorThemeText));
    _label->setPalette(p);
}

void QtMaterializerLabel::updateFont()
{
    _label->setFont(QtMaterialStyle::instance().themeFont(Material::FontBody1));
}

bool QtMaterializerLabel::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type())
    {
        case QEvent::StyleChange:
        {
            updateColors();
            updateFont();
            break;
        }

        default:
            break;
    }

    return QObject::eventFilter(watched, event);
}
