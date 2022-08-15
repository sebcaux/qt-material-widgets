#include "qtmaterialappbar_internal.h"

/*!
 *  \internal
 */
QtMaterialAppBarLayout::QtMaterialAppBarLayout(QWidget *parent)
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
    // TODO add actions
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

    if (_navButton != nullptr)
    {
        _navButton->setGeometry(0, 0, h, h);
        x += h;
    }
    _titleLabel->setGeometry(x, 0, rect.width() - x, h);
}
