#include "xx/qtmaterialselectfield.h"
#include "xx/qtmaterialselectfield_p.h"
#include <QEvent>
#include <QFontDatabase>
#include <QEasingCurve>
#include <QTimer>
#include <QPainter>
#include "xxlib/qtmaterialstyle.h"
#include "xx/qtmaterialmenuitem.h"
#include "xx/qtmaterialcollapsiblemenu.h"
#include "xxlib/qtmaterialoverlaywidget.h"

/*!
 *  \class QtMaterialSelectFieldPrivate
 *  \internal
 */

QtMaterialSelectFieldPrivate::QtMaterialSelectFieldPrivate(QtMaterialSelectField *q)
    : q_ptr(q)
{
}

QtMaterialSelectFieldPrivate::~QtMaterialSelectFieldPrivate()
{
}

void QtMaterialSelectFieldPrivate::init()
{
    Q_Q(QtMaterialSelectField);

    menuOverlay    = new QtMaterialOverlayWidget(q);
    menu           = new QtMaterialCollapsibleMenu;
    selectedIndex  = -1;
    useThemeColors = true;

    q->setStyle(&QtMaterialStyle::instance());

    QFontDatabase db;
    QFont font(db.font("Roboto", "Regular", 11));
    q->setFont(font);

    menuOverlay->setParent(q->parentWidget());
    menuOverlay->setAttribute(Qt::WA_TransparentForMouseEvents);
    menuOverlay->installEventFilter(q);

    menu->setParent(menuOverlay);
    menu->setMaximumHeight(300);
    menu->setCollapsedXScale(1);
    menu->setExpandYDuration(280);
    menu->setExpandYEasingCurve(QEasingCurve::OutQuad);

    QObject::connect(menu, SIGNAL(aboutToCollapse()), q, SLOT(makeTransparent()));
    QObject::connect(menu, SIGNAL(wasExpanded()), q, SLOT(makeOpaque()));
    QObject::connect(menu, SIGNAL(aboutToExpand()), menuOverlay, SLOT(raise()));
    QObject::connect(menu, SIGNAL(itemClicked(int)), q, SLOT(setSelectedIndex(int)));
    QObject::connect(menu, SIGNAL(itemClicked(int)), q, SLOT(collapseDelayed()));
    QObject::connect(menu, SIGNAL(itemClicked(int)), q, SIGNAL(itemSelected(int)));
}

/*!
 *  \class QtMaterialSelectField
 */

QtMaterialSelectField::QtMaterialSelectField(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialSelectFieldPrivate(this))
{
    d_func()->init();
}

QtMaterialSelectField::~QtMaterialSelectField()
{
}

/*!
 *  \reimp
 */
QSize QtMaterialSelectField::sizeHint() const
{
    return QSize(300, 30);
}

void QtMaterialSelectField::addItem(const QString &text)
{
    Q_D(QtMaterialSelectField);

    QtMaterialMenuItem *item = new QtMaterialMenuItem;
    item->setText(text);
    item->setHaloVisible(false);

    d->menu->addMenuItem(item);
}

QtMaterialMenuItem *QtMaterialSelectField::itemAt(int index) const
{
    Q_D(const QtMaterialSelectField);

    return d->menu->menuItemAt(index);
}

void QtMaterialSelectField::setPlaceholderText(const QString &text)
{
    Q_D(QtMaterialSelectField);

    d->placeholderText = text;
    update();
}

QString QtMaterialSelectField::placeholderText() const
{
    Q_D(const QtMaterialSelectField);

    return d->placeholderText;
}

void QtMaterialSelectField::setUseThemeColors(bool value)
{
    Q_D(QtMaterialSelectField);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialSelectField::useThemeColors() const
{
    Q_D(const QtMaterialSelectField);

    return d->useThemeColors;
}

void QtMaterialSelectField::setUnderlineColor(const QColor &color)
{
    Q_D(QtMaterialSelectField);

    d->underlineColor = color;
    setUseThemeColors(false);
}

QColor QtMaterialSelectField::underlineColor() const
{
    Q_D(const QtMaterialSelectField);

    if (d->useThemeColors || !d->underlineColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("border");
    }
    return d->underlineColor;
}

void QtMaterialSelectField::setPlaceholderColor(const QColor &color)
{
    Q_D(QtMaterialSelectField);

    d->placeholderColor = color;
    setUseThemeColors(false);
}

QColor QtMaterialSelectField::placeholderColor() const
{
    Q_D(const QtMaterialSelectField);

    if (d->useThemeColors || !d->placeholderColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("accent3");
    }
    return d->placeholderColor;
}

void QtMaterialSelectField::setForegroundColor(const QColor &color)
{
    Q_D(QtMaterialSelectField);

    d->foregroundColor = color;
    setUseThemeColors(false);
}

QColor QtMaterialSelectField::foregroundColor() const
{
    Q_D(const QtMaterialSelectField);

    if (d->useThemeColors || !d->foregroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    }
    return d->foregroundColor;
}

void QtMaterialSelectField::setHighlightedColor(const QColor &color)
{
    Q_D(QtMaterialSelectField);

    d->highlightedColor = color;
    setUseThemeColors(false);
}

QColor QtMaterialSelectField::highlightedColor() const
{
    Q_D(const QtMaterialSelectField);

    if (d->useThemeColors || !d->highlightedColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    }
    return d->highlightedColor;
}

void QtMaterialSelectField::setDisabledColor(const QColor &color)
{
    Q_D(QtMaterialSelectField);

    d->disabledColor = color;
    setUseThemeColors(false);
}

QColor QtMaterialSelectField::disabledColor() const
{
    Q_D(const QtMaterialSelectField);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("disabled");
    }
    return d->disabledColor;
}

void QtMaterialSelectField::setSelectedIndex(int index)
{
    Q_D(QtMaterialSelectField);

    QtMaterialMenuItem *menuItem;

    if (d->selectedIndex > -1 && (menuItem = d->menu->menuItemAt(d->selectedIndex))) {
        menuItem->setHighlighted(false);
    }
    if (index > -1 && (menuItem = d->menu->menuItemAt(index))) {
        menuItem->setHighlighted(true);
        d->selectedText = menuItem->text();
    }
    d->selectedIndex = index;
    update();
}

void QtMaterialSelectField::clearSelection()
{
    Q_D(QtMaterialSelectField);

    setSelectedIndex(-1);
    d->selectedText.clear();
}

void QtMaterialSelectField::makeTransparent()
{
    Q_D(QtMaterialSelectField);

    d->menuOverlay->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void QtMaterialSelectField::makeOpaque()
{
    Q_D(QtMaterialSelectField);

    d->menuOverlay->setAttribute(Qt::WA_TransparentForMouseEvents, false);
}

void QtMaterialSelectField::collapseDelayed()
{
    Q_D(QtMaterialSelectField);

    QTimer::singleShot(200, d->menu, SLOT(collapse()));
}

/*!
 *  \reimp
 */
bool QtMaterialSelectField::event(QEvent *event)
{
    Q_D(QtMaterialSelectField);

    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize:
    {
        const QSize sh = d->menu->sizeHint();
        d->menu->setGeometry(x(), y(), width(), sh.height());
        break;
    }
    case QEvent::MouseButtonRelease:
    {
        if (isEnabled()) {
            QtMaterialMenuItem *item;
            for (int i = 0; i < d->menu->itemCount(); ++i) {
                item = d->menu->menuItemAt(i);
                if (item->isHighlighted()) {
                    item->setForegroundColor(highlightedColor());
                } else {
                    item->setForegroundColor(foregroundColor());
                }
            }
            d->menu->expand();
        }
        break;
    }
    case QEvent::ParentChange:
    {
        QWidget *widget;
        if ((widget = parentWidget())) {
            d->menuOverlay->setParent(widget);
        }
        break;
    }
    default:
        break;
    }
    return QWidget::event(event);
}

/*!
 *  \reimp
 */
bool QtMaterialSelectField::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(QtMaterialSelectField);

    if (QEvent::MouseButtonPress == event->type()) {
        d->menu->collapse();
    }
    return QWidget::eventFilter(obj, event);
}

/*!
 *  \reimp
 */
void QtMaterialSelectField::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialSelectField);

    QPainter painter(this);

    const int y = height()-1;
    const int wd = width()-5;

    if (d->selectedText.isEmpty() && !d->placeholderText.isEmpty()) {
        if (isEnabled()) {
            painter.setPen(placeholderColor());
        } else {
            painter.setPen(disabledColor());
        }
        painter.drawText(2, y-8, d->placeholderText);
    } else {
        painter.drawText(2, y-8, d->selectedText);
    }

    QPen pen;
    pen.setWidth(1);
    pen.setColor(underlineColor());
    painter.setPen(pen);
    painter.setOpacity(1);
    painter.drawLine(2.5, y, wd, y);

    if (isEnabled())
    {
        static const int points[] = { wd-14, 12, wd-4, 12, wd-9, 18 };

        QPolygon polygon;
        polygon.setPoints(3, points);

        painter.setPen(Qt::NoPen);
        painter.setBrush(underlineColor());
        painter.drawPolygon(polygon);
    }
}
