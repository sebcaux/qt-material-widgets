#include "qtmaterialappbar_internal.h"

#include "qtmaterialappbar.h"
#include "qtmaterialiconbutton.h"

#include <QAction>

/*!
 *  \class QToolBarItem
 *  \internal
 */
QtMaterialAppBarLayoutItem::QtMaterialAppBarLayoutItem(QWidget *widget)
    : QWidgetItem(widget),
      action(0)
{
}

/*!
 *  \internal
 */
bool QtMaterialAppBarLayoutItem::isEmpty() const
{
    return action == 0 || !action->isVisible();
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
}

/*!
 *  \internal
 */
void QtMaterialAppBarLayout::insertAction(int index, QAction *action)
{
    Q_UNUSED(index);

    QtMaterialAppBar *appBar = dynamic_cast<QtMaterialAppBar *>(parentWidget());

    QtMaterialIconButton *iconButton = new QtMaterialIconButton(action->icon(), appBar);
    iconButton->setIconSize(QSize(48, 48));
    iconButton->setColor(appBar->foregroundColor());
    iconButton->setFixedWidth(64);
    connect(iconButton, &QtMaterialIconButton::clicked, action, &QAction::trigger);

    _actionIconButtons.push_back(new QtMaterialAppBarLayoutItem(iconButton));
}

/*!
 *  \internal
 */
void QtMaterialAppBarLayout::updateActions()
{
    QtMaterialAppBar *appBar = dynamic_cast<QtMaterialAppBar *>(parentWidget());

    for (QtMaterialAppBarLayoutItem *item : qAsConst(_actionIconButtons))
    {
        QtMaterialIconButton *iconButton = dynamic_cast<QtMaterialIconButton *>(item->widget());

        iconButton->setColor(appBar->foregroundColor());
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
}

/*!
 *  \internal
 */
QSize QtMaterialAppBarLayout::sizeHint() const
{
    return QSize(64, 64);
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
    return QSize(64, 64);
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
    int h = 64;
    int x = 0;
    int w = rect.width();

    if (_navButton != nullptr)
    {
        _navButton->setGeometry(0, 0, h, h);
        x += h;
    }

    int itemId = _actionIconButtons.count();
    for (QtMaterialAppBarLayoutItem *item : _actionIconButtons)
    {
        item->widget()->setGeometry(rect.width() - itemId * 64, 0, 64, 64);
        itemId--;
        w -= 64;
    }

    _titleLabel->setGeometry(x, 0, w - x, h);
}
