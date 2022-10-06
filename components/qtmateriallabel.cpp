#include "qtmateriallabel.h"

#include "lib/qtmaterialstyle.h"

#include "qcoreevent.h"
#include "qtmateriallabel_p.h"

/*!
 *  \class QtMaterialLabelPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialLabelPrivate::QtMaterialLabelPrivate(QtMaterialLabel *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialLabelPrivate::~QtMaterialLabelPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialLabelPrivate::init()
{
    fontType = Material::FontBody1;

    useThemeColors = true;
    updateColors();
    updateFont();
}

/*!
 *  \internal
 */
void QtMaterialLabelPrivate::updateColors()
{
    Q_Q(QtMaterialLabel);

    QPalette p = q->palette();
    p.setColor(QPalette::WindowText, q->color());
    q->setPalette(p);
}

/*!
 *  \internal
 */
void QtMaterialLabelPrivate::updateFont()
{
    Q_Q(QtMaterialLabel);

    q->setFont(QtMaterialStyle::instance().themeFont(fontType));
}

/*!
 *  \class QtMaterialLabel
 */

QtMaterialLabel::QtMaterialLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f),
      d_ptr(new QtMaterialLabelPrivate(this))
{
    d_func()->init();
}

QtMaterialLabel::QtMaterialLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel(text, parent, f),
      d_ptr(new QtMaterialLabelPrivate(this))
{
    d_func()->init();
}

QtMaterialLabel::~QtMaterialLabel()
{
}

Material::FontType QtMaterialLabel::fontType() const
{
    Q_D(const QtMaterialLabel);

    return d->fontType;
}

void QtMaterialLabel::setFontType(Material::FontType fontType)
{
    Q_D(QtMaterialLabel);

    d->fontType = fontType;
    setFont(QtMaterialStyle::instance().themeFont(fontType));
}

bool QtMaterialLabel::useThemeColors() const
{
    Q_D(const QtMaterialLabel);

    return d->useThemeColors;
}

void QtMaterialLabel::setUseThemeColors(bool value)
{
    Q_D(QtMaterialLabel);

    if (d->useThemeColors == value)
    {
        return;
    }

    d->useThemeColors = value;
    d->updateColors();
    d->updateFont();
}

QColor QtMaterialLabel::color() const
{
    Q_D(const QtMaterialLabel);

    if (d->useThemeColors || !d->color.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeText);
    }
    return d->color;
}

void QtMaterialLabel::setColor(const QColor &color)
{
    Q_D(QtMaterialLabel);

    d->color = color;

    d->useThemeColors = false;
    d->updateColors();
}

bool QtMaterialLabel::event(QEvent *event)
{
    Q_D(QtMaterialLabel);

    switch (event->type())
    {
        case QEvent::StyleChange:
        {
            d->updateColors();
            d->updateFont();
            break;
        }

        default:
            break;
    }
    return QLabel::event(event);
}
