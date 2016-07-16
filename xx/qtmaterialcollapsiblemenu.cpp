#include "xx/qtmaterialcollapsiblemenu.h"
#include "xx/qtmaterialcollapsiblemenu_p.h"
#include <QScrollArea>
#include <QStackedLayout>
#include <QPropertyAnimation>
#include "xx/qtmaterialcollapsiblemenu_internal.h"
#include "xx/qtmaterialmenuitem.h"
#include "xx/qtmaterialscrollbar.h"
#include "xxlib/qtmaterialstyle.h"

/*!
 *  \class QtMaterialCollapsibleMenuPrivate
 *  \internal
 */

QtMaterialCollapsibleMenuPrivate::QtMaterialCollapsibleMenuPrivate(QtMaterialCollapsibleMenu *q)
    : q_ptr(q)
{
}

QtMaterialCollapsibleMenuPrivate::~QtMaterialCollapsibleMenuPrivate()
{
}

void QtMaterialCollapsibleMenuPrivate::init()
{
    Q_Q(QtMaterialCollapsibleMenu);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    QtMaterialScrollBar *scrollBar = new QtMaterialScrollBar;

    scrollArea   = new QScrollArea;
    mainWidget   = new QWidget;
    menuLayout   = new QVBoxLayout;
    proxy        = new QtMaterialCollapsibleMenuProxy(mainWidget, effect);
    stateMachine = new QtMaterialCollapsibleMenuStateMachine(proxy, q);
    proxyStack   = new QStackedLayout;

    mainWidget->setLayout(menuLayout);
    menuLayout->setSpacing(0);
    menuLayout->setMargin(0);

    scrollArea->setLineWidth(0);
    scrollArea->setMidLineWidth(0);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(mainWidget);
    scrollArea->setVerticalScrollBar(scrollBar);
    scrollBar->setHideOnMouseOut(false);

    proxyStack->addWidget(scrollArea);
    proxyStack->setSpacing(0);
    proxyStack->setMargin(0);
    proxyStack->addWidget(proxy);
    proxyStack->setCurrentIndex(1);

    q->setLayout(proxyStack);

    effect->setBlurRadius(9);
    effect->setOffset(QPoint(0, 0));
    effect->setColor(QColor(0, 0, 0, 100));
    q->setGraphicsEffect(effect);

    stateMachine->start();
}

/*!
 *  \class QtMaterialCollapsibleMenu
 */

QtMaterialCollapsibleMenu::QtMaterialCollapsibleMenu(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialCollapsibleMenuPrivate(this))
{
    d_func()->init();
}

QtMaterialCollapsibleMenu::~QtMaterialCollapsibleMenu()
{
}

void QtMaterialCollapsibleMenu::addMenuItem(const QString &text)
{
    QtMaterialMenuItem *item = new QtMaterialMenuItem;
    item->setText(text);
    addMenuItem(item);
}

void QtMaterialCollapsibleMenu::addMenuItem(QtMaterialMenuItem *item)
{
    Q_D(QtMaterialCollapsibleMenu);

    d->menuLayout->addWidget(item);
    connect(item, SIGNAL(clicked(bool)), this, SLOT(menuItemClicked()));
}

QtMaterialMenuItem *QtMaterialCollapsibleMenu::menuItemAt(int index) const
{
    Q_D(const QtMaterialCollapsibleMenu);

    QLayoutItem *item;

    if (!(item = d->menuLayout->itemAt(index))) {
        return 0;
    }
    return static_cast<QtMaterialMenuItem *>(item->widget());
}

int QtMaterialCollapsibleMenu::itemCount() const
{
    Q_D(const QtMaterialCollapsibleMenu);

    return d->menuLayout->count();
}

void QtMaterialCollapsibleMenu::scrollTo(int dx, int dy)
{
    Q_D(QtMaterialCollapsibleMenu);

    d->scrollArea->horizontalScrollBar()->setValue(dx);
    d->scrollArea->verticalScrollBar()->setValue(dy);
}

void QtMaterialCollapsibleMenu::setExpandXDuration(int duration)
{
    Q_D(QtMaterialCollapsibleMenu);

    d->stateMachine->expandXAnimation()->setDuration(duration);
}

void QtMaterialCollapsibleMenu::setExpandXEasingCurve(const QEasingCurve &curve)
{
    Q_D(QtMaterialCollapsibleMenu);

    d->stateMachine->expandXAnimation()->setEasingCurve(curve);
}

void QtMaterialCollapsibleMenu::setExpandYDuration(int duration)
{
    Q_D(QtMaterialCollapsibleMenu);

    d->stateMachine->expandYAnimation()->setDuration(duration);
}

void QtMaterialCollapsibleMenu::setExpandYEasingCurve(const QEasingCurve &curve)
{
    Q_D(QtMaterialCollapsibleMenu);

    d->stateMachine->expandYAnimation()->setEasingCurve(curve);
}

void QtMaterialCollapsibleMenu::setCollapseXDuration(int duration)
{
    Q_D(QtMaterialCollapsibleMenu);

    d->stateMachine->collapseXAnimation()->setDuration(duration);
}

void QtMaterialCollapsibleMenu::setCollapseXEasingCurve(const QEasingCurve &curve)
{
    Q_D(QtMaterialCollapsibleMenu);

    d->stateMachine->collapseXAnimation()->setEasingCurve(curve);
}

void QtMaterialCollapsibleMenu::setCollapseYDuration(int duration)
{
    Q_D(QtMaterialCollapsibleMenu);

    d->stateMachine->collapseYAnimation()->setDuration(duration);
}

void QtMaterialCollapsibleMenu::setCollapseYEasingCurve(const QEasingCurve &curve)
{
    Q_D(QtMaterialCollapsibleMenu);

    d->stateMachine->collapseYAnimation()->setEasingCurve(curve);
}

void QtMaterialCollapsibleMenu::setCollapsedXScale(qreal sx)
{
    Q_D(QtMaterialCollapsibleMenu);

    d->stateMachine->collapsedState()->assignProperty(d->proxy, "xScale", sx);
}

void QtMaterialCollapsibleMenu::setCollapsedYScale(qreal sy)
{
    Q_D(QtMaterialCollapsibleMenu);

    d->stateMachine->collapsedState()->assignProperty(d->proxy, "xScale", sy);
}

void QtMaterialCollapsibleMenu::collapse()
{
    Q_D(QtMaterialCollapsibleMenu);

    d->proxyStack->setCurrentIndex(1);
    emit d->proxy->collapse();
    emit aboutToCollapse();
}

void QtMaterialCollapsibleMenu::expand()
{
    Q_D(QtMaterialCollapsibleMenu);

    d->proxyStack->setCurrentIndex(1);
    emit d->proxy->expand();
    emit aboutToExpand();
}

void QtMaterialCollapsibleMenu::menuItemClicked()
{
    Q_D(QtMaterialCollapsibleMenu);

    QWidget *widget = static_cast<QWidget *>(sender());
    if (widget) {
        int index = d->menuLayout->indexOf(widget);
        emit itemClicked(index);
    }
}

void QtMaterialCollapsibleMenu::setOpaque()
{
    Q_D(QtMaterialCollapsibleMenu);

    d->proxyStack->setCurrentIndex(0);
}
