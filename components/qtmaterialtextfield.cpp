#include "qtmaterialtextfield.h"

#include "lib/qtmaterialstyle.h"
#include "qtmaterialtextfield_internal.h"
#include "qtmaterialtextfield_p.h"

#include <QApplication>
#include <QPainter>
#include <QPainterPath>

/*!
 *  \class QtMaterialTextFieldPrivate
 *  \internal
 */

QtMaterialTextFieldPrivate::QtMaterialTextFieldPrivate(QtMaterialTextField *q)
    : q_ptr(q)
{
}

QtMaterialTextFieldPrivate::~QtMaterialTextFieldPrivate()
{
}

void QtMaterialTextFieldPrivate::init()
{
    Q_Q(QtMaterialTextField);

    stateMachine = new QtMaterialTextFieldStateMachine(q);
    label = nullptr;

    labelFontSize = 9.5;
    labelVisible = false;
    inputLineVisible = true;
    useThemeColors = true;

    q->setFrame(false);
    q->setStyle(&QtMaterialStyle::instance());
    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);
    q->setTextMargins(0, 2, 0, 4);

    q->setFont(QtMaterialStyle::instance().themeFont(Material::FontBody1));

    QPalette p = q->palette();
    p.setColor(QPalette::Base, QColor(0, 0, 0, 0));
    p.setColor(QPalette::Text, q->textColor());
    q->setPalette(p);

    stateMachine->start();
    QCoreApplication::processEvents();
}

/*!
 *  \class QtMaterialTextField
 */

QtMaterialTextField::QtMaterialTextField(QWidget *parent)
    : QLineEdit(parent),
      d_ptr(new QtMaterialTextFieldPrivate(this))
{
    d_func()->init();
}

QtMaterialTextField::~QtMaterialTextField()
{
}

void QtMaterialTextField::setUseThemeColors(bool value)
{
    Q_D(QtMaterialTextField);

    if (d->useThemeColors == value)
    {
        return;
    }

    d->useThemeColors = value;

    QPalette p = palette();
    p.setColor(QPalette::Text, textColor());
    setPalette(p);

    d->stateMachine->setupProperties();
}

bool QtMaterialTextField::useThemeColors() const
{
    Q_D(const QtMaterialTextField);

    return d->useThemeColors;
}

void QtMaterialTextField::setLabelVisible(bool value)
{
    Q_D(QtMaterialTextField);

    if (d->labelVisible == value)
    {
        return;
    }

    d->labelVisible = value;

    if ((d->label == nullptr) && value)
    {
        d->label = new QtMaterialTextFieldLabel(this);
        d->stateMachine->setLabel(d->label);
    }

    if (value)
    {
        setContentsMargins(0, 23, 0, 0);
    }
    else
    {
        setContentsMargins(0, 0, 0, 0);
    }
}

bool QtMaterialTextField::labelVisible() const
{
    Q_D(const QtMaterialTextField);

    return d->labelVisible;
}

void QtMaterialTextField::setLabelFontSize(qreal size)
{
    Q_D(QtMaterialTextField);

    d->labelFontSize = size;

    if (d->label != nullptr)
    {
        QFont font(d->label->font());
        font.setPointSizeF(size);
        d->label->setFont(font);
        d->label->update();
    }
}

qreal QtMaterialTextField::labelFontSize() const
{
    Q_D(const QtMaterialTextField);

    return d->labelFontSize;
}

void QtMaterialTextField::setLabelText(const QString &label)
{
    Q_D(QtMaterialTextField);

    d->labelText = label;
    setLabelVisible(true);
    d->label->update();
}

const QString &QtMaterialTextField::labelText() const
{
    Q_D(const QtMaterialTextField);

    return d->labelText;
}

void QtMaterialTextField::setTextColor(const QColor &color)
{
    Q_D(QtMaterialTextField);

    d->textColor = color;
    d->useThemeColors = false;

    QPalette p = palette();
    p.setColor(QPalette::Text, d->textColor);
    setPalette(p);

    d->stateMachine->setupProperties();
}

QColor QtMaterialTextField::textColor() const
{
    Q_D(const QtMaterialTextField);

    if (d->useThemeColors || !d->textColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeText);
    }

    return d->textColor;
}

void QtMaterialTextField::setLabelColor(const QColor &color)
{
    Q_D(QtMaterialTextField);

    d->labelColor = color;

    d->useThemeColors = false;
    d->stateMachine->setupProperties();
}

QColor QtMaterialTextField::labelColor() const
{
    Q_D(const QtMaterialTextField);

    if (d->useThemeColors || !d->labelColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeSecondaryDark);
    }

    return d->labelColor;
}

void QtMaterialTextField::setInkColor(const QColor &color)
{
    Q_D(QtMaterialTextField);

    d->inkColor = color;

    d->useThemeColors = false;
    d->stateMachine->setupProperties();
}

QColor QtMaterialTextField::inkColor() const
{
    Q_D(const QtMaterialTextField);

    if (d->useThemeColors || !d->inkColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemePrimaryMain);
    }

    return d->inkColor;
}

void QtMaterialTextField::setInputLineColor(const QColor &color)
{
    Q_D(QtMaterialTextField);

    d->inputLineColor = color;

    d->useThemeColors = false;
    d->stateMachine->setupProperties();
}

QColor QtMaterialTextField::inputLineColor() const
{
    Q_D(const QtMaterialTextField);

    if (d->useThemeColors || !d->inputLineColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor(Material::ColorThemeBorder);
    }

    return d->inputLineColor;
}

void QtMaterialTextField::setInputLineVisible(bool value)
{
    Q_D(QtMaterialTextField);

    if (d->inputLineVisible == value)
    {
        return;
    }

    d->inputLineVisible = value;
    update();
}

bool QtMaterialTextField::inputLineVisible() const
{
    Q_D(const QtMaterialTextField);

    return d->inputLineVisible;
}

QtMaterialTextField::QtMaterialTextField(QtMaterialTextFieldPrivate &d, QWidget *parent)
    : QLineEdit(parent),
      d_ptr(&d)
{
    d_func()->init();
}

/*!
 *  \reimp
 */
bool QtMaterialTextField::event(QEvent *event)
{
    Q_D(QtMaterialTextField);

    switch (event->type())
    {
        case QEvent::Resize:
        case QEvent::Move:
        {
            if (d->label != nullptr)
            {
                d->label->setGeometry(rect());
            }
        }

        case QEvent::StyleChange:
        {
            d->stateMachine->setupProperties();
            break;
        }

        default:
            break;
    }
    return QLineEdit::event(event);
}

/*!
 *  \reimp
 */
void QtMaterialTextField::paintEvent(QPaintEvent *event)
{
    Q_D(QtMaterialTextField);

    const qreal progress = d->stateMachine->progress();

    QPainter painterBg(this);

    qreal bgBase = 70;
    if (underMouse())
    {
        bgBase = 150;
    }
    QColor bgColor(0xe8, 0xe8, 0xe8, bgBase + progress * (255 - bgBase));
    painterBg.setBrush(bgColor);
    painterBg.setPen(QPen(Qt::NoPen));
    QPainterPath path;
    qreal w = rect().width();
    qreal h = rect().height();
    qreal r = 10;
    path.arcMoveTo(0, 0, r, r, 180);
    path.arcTo(0, 0, r, r, 180, -90);
    path.arcTo(w - r, 0, r, r, 90, -90);
    path.lineTo(w, h);
    path.lineTo(0, h);
    path.closeSubpath();
    painterBg.drawPath(path);

    painterBg.end();

    QLineEdit::paintEvent(event);

    QPainter painter(this);

    if (text().isEmpty() && progress < 1)
    {
        // TODO bug when placeholder
        painter.setBrush(bgColor);
        painter.setPen(QPen(Qt::NoPen));
        painter.drawPath(path);
    }

    if (d->inputLineVisible)
    {
        const int wd = width();
        const int y = height() - 1;
        QPen pen;
        pen.setWidth(1);
        pen.setColor(inputLineColor());

        if (!isEnabled())
        {
            pen.setStyle(Qt::DashLine);
        }

        painter.setPen(pen);
        painter.setOpacity(1);
        painter.drawLine(QLineF(2.5, y, wd, y));

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(inkColor());

        if (progress > 0)
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(brush);
            const int w = (1 - progress) * static_cast<qreal>(wd / 2);
            painter.drawRect(w, height() - 2, wd - w * 2, 2);
        }
    }
}
