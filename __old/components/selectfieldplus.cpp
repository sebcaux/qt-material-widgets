#include "selectfieldplus.h"
#include <QPainter>
#include <QFontDatabase>
#include <QEvent>
#include <QEasingCurve>
#include <QLayout>
#include <QTimer>
#include "xxlib/qtmaterialstyle.h"
#include "xxlib/qtmaterialoverlaywidget.h"
#include "xx/qtmaterialcollapsiblemenu.h"
#include "xx/qtmaterialmenuitem.h"
#include <QDebug>

SelectFieldPlus::SelectFieldPlus(QWidget *parent)
    : QWidget(parent)
{
    //setText("Hello");
    //setMinimumWidth(200);

    setStyle(&QtMaterialStyle::instance());

    QFontDatabase db;
    QFont font(db.font("Roboto", "Regular", 11));
    setFont(font);

    _menuOverlay = new QtMaterialOverlayWidget(this);
    _menu = new QtMaterialCollapsibleMenu;
    _selectedIndex = -1;

    _menuOverlay->setParent(parentWidget());
    _menuOverlay->setAttribute(Qt::WA_TransparentForMouseEvents);
    _menuOverlay->installEventFilter(this);

    _menu->setParent(_menuOverlay);
    _menu->setMaximumHeight(300);
    _menu->setCollapsedXScale(1);
    _menu->setExpandYDuration(280);
    _menu->setExpandYEasingCurve(QEasingCurve::OutQuad);

    QObject::connect(_menu, SIGNAL(aboutToCollapse()), this, SLOT(makeTransparent()));
    QObject::connect(_menu, SIGNAL(wasExpanded()), this, SLOT(makeOpaque()));
    QObject::connect(_menu, SIGNAL(aboutToExpand()), _menuOverlay, SLOT(raise()));
    QObject::connect(_menu, SIGNAL(itemClicked(int)), this, SLOT(setSelectedIndex(int)));
    QObject::connect(_menu, SIGNAL(itemClicked(int)), this, SLOT(collapseDelayed()));
    QObject::connect(_menu, SIGNAL(itemClicked(int)), this, SIGNAL(itemSelected(int)));

    //

    {
        QtMaterialMenuItem *b;

        b = new QtMaterialMenuItem;
        b->setText("Hello 123");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Select everything");
        b->setIcon(QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
        _menu->addMenuItem(b);
        //b->setForegroundColor(Qt::red);

        b = new QtMaterialMenuItem;
        b->setText("Run something");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Download internet");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Done");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Run something");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Download internet");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Done");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Select everything");
        b->setIcon(QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Run something");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Download internet");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Done");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Run something");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Download internet");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Done");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Select everything");
        b->setIcon(QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Run something");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Download internet");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Done");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Run something");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Download internet");
        _menu->addMenuItem(b);

        b = new QtMaterialMenuItem;
        b->setText("Done");
        _menu->addMenuItem(b);
    }
}

SelectFieldPlus::~SelectFieldPlus()
{
}

QSize SelectFieldPlus::sizeHint() const
{
    return QSize(300, 30);
}

QColor SelectFieldPlus::underlineColor() const
{
    // @TODO

    return QtMaterialStyle::instance().themeColor("border");
}

void SelectFieldPlus::setSelectedIndex(int index)
{
    QtMaterialMenuItem *menuItem;

    if (_selectedIndex > -1 && (menuItem = _menu->menuItemAt(_selectedIndex))) {
        menuItem->setHighlighted(false);
    }
    if (index > -1 && (menuItem = _menu->menuItemAt(index))) {
        menuItem->setHighlighted(true);
        _selectedText = menuItem->text();
        update();
    }
    _selectedIndex = index;
}

void SelectFieldPlus::makeTransparent()
{
    _menuOverlay->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void SelectFieldPlus::makeOpaque()
{
    _menuOverlay->setAttribute(Qt::WA_TransparentForMouseEvents, false);
}

void SelectFieldPlus::collapseDelayed()
{
    QTimer::singleShot(200, _menu, SLOT(collapse()));
}

bool SelectFieldPlus::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize:
    {
        const QSize sh = _menu->sizeHint();
        _menu->setGeometry(x(), y(), width(), sh.height());
        break;
    }
    case QEvent::MouseButtonRelease:
    {
        QtMaterialMenuItem *item;
        for (int i = 0; i < _menu->itemCount(); ++i) {
            item = _menu->menuItemAt(i);
            if (item->isHighlighted()) {
                item->setForegroundColor(QtMaterialStyle::instance().themeColor("primary1"));
            } else {
                item->setForegroundColor(QtMaterialStyle::instance().themeColor("text"));
            }
        }
        if ((item = _menu->menuItemAt(_selectedIndex))) {
            _menu->scrollTo(0, item->pos().y());
        }
        _menu->expand();
        break;
    }
    case QEvent::ParentChange:
    {
        QWidget *widget;
        if ((widget = parentWidget())) {
            _menuOverlay->setParent(widget);
        }
        break;
    }
    default:
        break;
    }
    return QWidget::event(event);
}

bool SelectFieldPlus::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::MouseButtonPress == event->type()) {
        _menu->collapse();
    }
    return QWidget::eventFilter(obj, event);
}

void SelectFieldPlus::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    //painter.drawRect(rect().adjusted(0, 0, -1, -1));

    const int y = height()-1;
    const int wd = width()-5;

    painter.drawText(2, y-8, _selectedText);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(underlineColor());
    painter.setPen(pen);
    painter.setOpacity(1);
    painter.drawLine(2.5, y, wd, y);

    static const int points[] = { wd-14, 12, wd-4, 12, wd-9, 18 };

    QPolygon polygon;
    polygon.setPoints(3, points);

    painter.setPen(Qt::NoPen);
    painter.setBrush(underlineColor());
    painter.drawPolygon(polygon);
}
