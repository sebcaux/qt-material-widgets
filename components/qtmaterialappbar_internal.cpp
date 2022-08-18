#include "qtmaterialappbar_internal.h"

#include "qtmaterialappbar.h"
#include "qtmaterialiconbutton.h"

#include <QAction>

/*!
 *  \class QToolBarItem
 *  \internal
 */
QtMaterialAppBarLayoutItem::QtMaterialAppBarLayoutItem(QWidget *widget, QAction *action)
    : QWidgetItem(widget),
      action(action)
{
}

/*!
 *  \internal
 */
bool QtMaterialAppBarLayoutItem::isEmpty() const
{
    return (action == nullptr) || (!action->isVisible());
}

/*!
 *  \class QtMaterialAppBarLayout
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialAppBarLayout::QtMaterialAppBarLayout(QtMaterialAppBar *parent)
    : QLayout(parent)
{
}

/*!
 *  \internal
 */
QtMaterialAppBarLayout::~QtMaterialAppBarLayout()
{
}

/*!
 *  \internal
 */
QtMaterialIconButton *QtMaterialAppBarLayout::navButton() const
{
    return _navButton;
}

/*!
 *  \internal
 */
void QtMaterialAppBarLayout::setNavButton(QtMaterialIconButton *navButton)
{
    _navButton = navButton;
    if (_navButton)
    {
        addChildWidget(_navButton);
    }
    invalidate();
}

/*!
 *  \internal
 */
void QtMaterialAppBarLayout::insertAction(int index, QAction *action)
{
    Q_UNUSED(index);

    QtMaterialAppBar *appBar = dynamic_cast<QtMaterialAppBar *>(parentWidget());

    QtMaterialIconButton *iconButton = new QtMaterialIconButton(action->icon(), appBar);
    iconButton->setIconSize(appBar->iconSize());
    iconButton->setColor(appBar->foregroundColor());
    iconButton->setToolTip(action->text());
    int size = appBar->iconSize().width() * 1.33;
    iconButton->setFixedSize(size, size);
    addChildWidget(iconButton);
    connect(iconButton, &QtMaterialIconButton::clicked, action, &QAction::trigger);

    _actionIconButtons.push_back(new QtMaterialAppBarLayoutItem(iconButton, action));
    invalidate();
}

/*!
 *  \internal
 */
void QtMaterialAppBarLayout::updateActions()
{
    for (QtMaterialAppBarLayoutItem *item : qAsConst(_actionIconButtons))
    {
        QtMaterialIconButton *iconButton = dynamic_cast<QtMaterialIconButton *>(item->widget());

        iconButton->setIcon(item->action->icon());
        iconButton->setToolTip(item->action->text());
    }
}

/*!
 *  \internal
 */
void QtMaterialAppBarLayout::updateButtons()
{
    QtMaterialAppBar *appBar = dynamic_cast<QtMaterialAppBar *>(parentWidget());

    int size = appBar->iconSize().width() * 1.33;
    for (QtMaterialAppBarLayoutItem *item : qAsConst(_actionIconButtons))
    {
        QtMaterialIconButton *iconButton = dynamic_cast<QtMaterialIconButton *>(item->widget());

        iconButton->setColor(appBar->foregroundColor());
        iconButton->setIconSize(appBar->iconSize());
        iconButton->setFixedSize(size, size);
    }
}

/*!
 *  \internal
 */
const QList<QtMaterialAppBarLayoutItem *> &QtMaterialAppBarLayout::actionIconButtons() const
{
    return _actionIconButtons;
}

/*!
 *  \internal
 */
QLabel *QtMaterialAppBarLayout::titleLabel() const
{
    return _titleLabel;
}

/*!
 *  \internal
 */
void QtMaterialAppBarLayout::setTitleLabel(QLabel *titleLabel)
{
    _titleLabel = titleLabel;
    if (_titleLabel)
    {
        addChildWidget(_titleLabel);
    }
    invalidate();
}

/*!
 *  \internal
 */
QSize QtMaterialAppBarLayout::sizeHint() const
{
    QtMaterialAppBar *appBar = dynamic_cast<QtMaterialAppBar *>(parentWidget());
    int size = appBar->iconSize().width() * 1.33;
    return QSize(size, size);
}

/*!
 *  \internal
 */
void QtMaterialAppBarLayout::addItem(QLayoutItem *)
{
}

/*!
 *  \internal
 */
QLayoutItem *QtMaterialAppBarLayout::itemAt(int index) const
{
    Q_UNUSED(index);
    return nullptr;
}

/*!
 *  \internal
 */
QLayoutItem *QtMaterialAppBarLayout::takeAt(int index)
{
    Q_UNUSED(index);
    return nullptr;
}

/*!
 *  \internal
 */
int QtMaterialAppBarLayout::count() const
{
    int c = 1;
    c += (_navButton == nullptr) ? 0 : 1;
    c += _actionIconButtons.count();
    return c;
}

/*!
 *  \internal
 */
QSize QtMaterialAppBarLayout::minimumSize() const
{
    QtMaterialAppBar *appBar = dynamic_cast<QtMaterialAppBar *>(parentWidget());
    int size = appBar->iconSize().width() * 1.33;
    return QSize(size, size);
}

/*!
 *  \internal
 */
QSize QtMaterialAppBarLayout::maximumSize() const
{
    return QSize();
}

/*!
 *  \internal
 */
Qt::Orientations QtMaterialAppBarLayout::expandingDirections() const
{
    return Qt::Horizontal;
}

/*!
 *  \internal
 */
void QtMaterialAppBarLayout::setGeometry(const QRect &rect)
{
    QtMaterialAppBar *appBar = dynamic_cast<QtMaterialAppBar *>(parentWidget());
    int size = appBar->iconSize().width() * 1.33;

    int h = size;
    int x = 0;
    int w = rect.width();

    if (_navButton != nullptr)
    {
        _navButton->setGeometry(0, 0, size, h);
        x += h;
    }

    int itemId = _actionIconButtons.count();
    for (QtMaterialAppBarLayoutItem *item : qAsConst(_actionIconButtons))
    {
        item->widget()->setGeometry(rect.width() - itemId * size, 0, size, size);
        itemId--;
        w -= size;
    }

    _titleLabel->setGeometry(x, 0, w - x, h);
}
