#include "qtmaterialbuttonlist.h"
#include "qtmaterialbuttonlist_p.h"

#include "lib/qtmaterialstyle.h"
#include "qtmaterialflatbutton.h"

#include <QPainter>
#include <QResizeEvent>

/*!
 *  \class QtMaterialButtonListPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialButtonListPrivate::QtMaterialButtonListPrivate(QtMaterialButtonList *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialButtonListPrivate::~QtMaterialButtonListPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialButtonListPrivate::init()
{
    useThemeColors = true;
}

/*!
 *  \internal
 */
QtMaterialFlatButton *QtMaterialButtonListPrivate::createButton(const QString &text, const QIcon &icon)
{
    Q_Q(QtMaterialButtonList);

    QtMaterialFlatButton *button = new QtMaterialFlatButton(text, Material::ButtonTextDefault, q);
    button->setFont(q->font());
    button->setTextAlignment(Qt::AlignLeft);
    button->setIcon(icon);
    button->setCornerRadius(0);
    button->setHaloVisible(false);
    button->setFixedHeight(50);
    button->setOverlayStyle(Material::TintedOverlay);

    button->raise();
    button->show();

    return button;
}

/*!
 *  \class QtMaterialButtonList
 */

QtMaterialButtonList::QtMaterialButtonList(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialButtonListPrivate(this))
{
    d_func()->init();
}

QtMaterialButtonList::~QtMaterialButtonList()
{
}

void QtMaterialButtonList::addButton(const QString &text)
{
    addButton(QIcon(), text);
}

void QtMaterialButtonList::addButton(const QIcon &icon, const QString &text)
{
    Q_D(QtMaterialButtonList);

    QtMaterialFlatButton *button = d->createButton(text, icon);

    d->buttons.append(button);
    updateGeometry();
}

void QtMaterialButtonList::insertButton(int index, const QString &text)
{
    insertButton(index, QIcon(), text);
}

void QtMaterialButtonList::insertButton(int index, const QIcon &icon, const QString &text)
{
    Q_D(QtMaterialButtonList);

    QtMaterialFlatButton *button = d->createButton(text, icon);

    d->buttons.insert(index, button);
    updateGeometry();
}

QString QtMaterialButtonList::buttonText(int index) const
{
    Q_D(const QtMaterialButtonList);

    if (const QtMaterialFlatButton *button = d->buttons.at(index))
    {
        return button->text();
    }

    return QString();
}

void QtMaterialButtonList::setButtonText(int index, const QString &text)
{
    Q_D(QtMaterialButtonList);

    if (QtMaterialFlatButton *button = d->buttons.at(index))
    {
        button->setText(text);
    }
}

QIcon QtMaterialButtonList::buttonIcon(int index) const
{
    Q_D(const QtMaterialButtonList);

    if (const QtMaterialFlatButton *button = d->buttons.at(index))
    {
        return button->icon();
    }

    return QIcon();
}

void QtMaterialButtonList::setButtonIcon(int index, const QIcon &icon)
{
    Q_D(QtMaterialButtonList);

    if (QtMaterialFlatButton *button = d->buttons.at(index))
    {
        button->setIcon(icon);
    }
}

int QtMaterialButtonList::count() const
{
    Q_D(const QtMaterialButtonList);

    return d->buttons.count();
}

void QtMaterialButtonList::setUseThemeColors(bool value)
{
    Q_D(QtMaterialButtonList);

    if (d->useThemeColors == value)
    {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialButtonList::useThemeColors() const
{
    Q_D(const QtMaterialButtonList);

    return d->useThemeColors;
}

void QtMaterialButtonList::setForegroundColor(const QColor &color)
{
    Q_D(QtMaterialButtonList);

    d->foregroundColor = color;

    if (d->useThemeColors)
    {
        d->useThemeColors = false;
    }
    update();
}

QColor QtMaterialButtonList::foregroundColor() const
{
    Q_D(const QtMaterialButtonList);

    if (d->useThemeColors || !d->foregroundColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeAlternateText);
    }

    return d->foregroundColor;
}

void QtMaterialButtonList::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialButtonList);

    d->backgroundColor = color;

    if (d->useThemeColors)
    {
        d->useThemeColors = false;
    }
    update();
}

QColor QtMaterialButtonList::backgroundColor() const
{
    Q_D(const QtMaterialButtonList);

    if (d->useThemeColors || !d->backgroundColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemePrimaryMain);
    }

    return d->backgroundColor;
}

void QtMaterialButtonList::resizeEvent(QResizeEvent *event)
{
    Q_D(QtMaterialButtonList);

    int y = 0;
    for (QtMaterialFlatButton *button : qAsConst(d->buttons))
    {
        button->setGeometry(0, y, event->size().width(), 50);
        y += 50;
    }
}

QSize QtMaterialButtonList::sizeHint() const
{
    return QSize(-1, count() * 50);
}
