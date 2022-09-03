#include "qtmaterialappbar_internal.h"

#include "qtmaterialappbar.h"
#include "qtmaterialbuttonlist.h"
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
    _appBar = dynamic_cast<QtMaterialAppBar *>(parentWidget());
    _navButton = nullptr;
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

    if (_actionIconButtons.count() < 3)
    {
        QtMaterialIconButton *iconButton = createIconButton(action);
        _actionIconButtons.push_back(new QtMaterialAppBarLayoutItem(iconButton, action));
        _visibleButtons.push_back(iconButton);
    }

    invalidate();
}

/*!
 *  \internal
 */
QtMaterialIconButton *QtMaterialAppBarLayout::createIconButton(QAction *action)
{
    QtMaterialIconButton *iconButton = new QtMaterialIconButton(action->icon(), _appBar);
    iconButton->setIconSize(_appBar->iconSize());
    iconButton->setColor(_appBar->foregroundColor());
    iconButton->setToolTip(action->text());
    addChildWidget(iconButton);
    connect(iconButton, &QtMaterialIconButton::clicked, action, &QAction::trigger);

    return iconButton;
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

    if (_navButton != nullptr)
    {
        _navButton->setColor(appBar->foregroundColor());
        _navButton->setIconSize(appBar->iconSize());
    }
    for (QtMaterialAppBarLayoutItem *item : qAsConst(_actionIconButtons))
    {
        QtMaterialIconButton *iconButton = dynamic_cast<QtMaterialIconButton *>(item->widget());

        iconButton->setColor(appBar->foregroundColor());
        iconButton->setIconSize(appBar->iconSize());
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

    int size = qMax(static_cast<int>(appBar->iconSize().height() * 1.33), _titleLabel->fontMetrics().height());
    int x = 0;
    int w = rect.width();

    if (_navButton != nullptr)
    {
        _navButton->setGeometry(0, 0, size, size);
        x += size;
    }

    int itemId = _visibleButtons.count();
    for (QtMaterialIconButton *icon : qAsConst(_visibleButtons))
    {
        icon->setGeometry(rect.width() - itemId * size, 0, size, size);
        itemId--;
        w -= size;
    }

    _titleLabel->setGeometry(x, 0, w - x, size);
}
