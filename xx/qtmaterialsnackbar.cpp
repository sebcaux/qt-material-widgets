#include "xx/qtmaterialsnackbar.h"
#include "xx/qtmaterialsnackbar_p.h"
#include <QApplication>
#include <QPainter>
#include "xx/qtmaterialsnackbar_internal.h"
#include "xxlib/qtmaterialstyle.h"

/*!
 *  \class QtMaterialSnackbarPrivate
 *  \internal
 */

QtMaterialSnackbarPrivate::QtMaterialSnackbarPrivate(QtMaterialSnackbar *q)
    : q_ptr(q)
{
}

QtMaterialSnackbarPrivate::~QtMaterialSnackbarPrivate()
{
}

void QtMaterialSnackbarPrivate::init()
{
    Q_Q(QtMaterialSnackbar);

    stateMachine   = new QtMaterialSnackbarStateMachine(q);
    duration       = 3000;
    boxWidth       = 300;
    useThemeColors = true;

    q->setAttribute(Qt::WA_TransparentForMouseEvents);

    stateMachine->start();
    QCoreApplication::processEvents();
}

/*!
 *  \class QtMaterialSnackbar
 */

QtMaterialSnackbar::QtMaterialSnackbar(QWidget *parent)
    : QtMaterialOverlayWidget(parent),
      d_ptr(new QtMaterialSnackbarPrivate(this))
{
    d_func()->init();
}

QtMaterialSnackbar::~QtMaterialSnackbar()
{
}

void QtMaterialSnackbar::setAutoHideDuration(int duration)
{
    Q_D(QtMaterialSnackbar);

    d->duration = duration;
}

int QtMaterialSnackbar::autoHideDuration() const
{
    Q_D(const QtMaterialSnackbar);

    return d->duration;
}

void QtMaterialSnackbar::setUseThemeColors(bool value)
{
    Q_D(QtMaterialSnackbar);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialSnackbar::useThemeColors() const
{
    Q_D(const QtMaterialSnackbar);

    return d->useThemeColors;
}

void QtMaterialSnackbar::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialSnackbar);

    d->backgroundColor = color;
    setUseThemeColors(false);
}

QColor QtMaterialSnackbar::backgroundColor() const
{
    Q_D(const QtMaterialSnackbar);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    } else {
        return d->backgroundColor;
    }
}

void QtMaterialSnackbar::setTextColor(const QColor &color)
{
    Q_D(QtMaterialSnackbar);

    d->textColor = color;
    setUseThemeColors(false);
}

QColor QtMaterialSnackbar::textColor() const
{
    Q_D(const QtMaterialSnackbar);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void QtMaterialSnackbar::setFontSize(qreal size)
{
    QFont f(font());
    f.setPointSizeF(size);
    setFont(f);

    update();
}

qreal QtMaterialSnackbar::fontSize() const
{
    return font().pointSizeF();
}

void QtMaterialSnackbar::setBoxWidth(int width)
{
    Q_D(QtMaterialSnackbar);

    d->boxWidth = width;
    update();
}

int QtMaterialSnackbar::boxWidth() const
{
    Q_D(const QtMaterialSnackbar);

    return d->boxWidth;
}

void QtMaterialSnackbar::addMessage(const QString &message)
{
}

void QtMaterialSnackbar::addInstantMessage(const QString &message)
{
}

void QtMaterialSnackbar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QPen p;
    p.setWidth(3);
    p.setColor(Qt::red);
    painter.setPen(p);
}
