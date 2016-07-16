#ifndef QTMATERIALCOLLAPSIBLEMENU_H
#define QTMATERIALCOLLAPSIBLEMENU_H

#include <QWidget>
#include <QScopedPointer>

class QtMaterialCollapsibleMenuPrivate;
class QtMaterialMenuItem;

class QtMaterialCollapsibleMenu : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialCollapsibleMenu(QWidget *parent = 0);
    ~QtMaterialCollapsibleMenu();

    void addMenuItem(const QString &text);
    void addMenuItem(QtMaterialMenuItem *item);

    QtMaterialMenuItem *menuItemAt(int index) const;
    int itemCount() const;

    void scrollTo(int dx, int dy);

    void setExpandXDuration(int duration);
    void setExpandXEasingCurve(const QEasingCurve &curve);

    void setExpandYDuration(int duration);
    void setExpandYEasingCurve(const QEasingCurve &curve);

    void setCollapseXDuration(int duration);
    void setCollapseXEasingCurve(const QEasingCurve &curve);

    void setCollapseYDuration(int duration);
    void setCollapseYEasingCurve(const QEasingCurve &curve);

    void setCollapsedXScale(qreal sx);
    void setCollapsedYScale(qreal sy);

signals:
    void aboutToExpand();
    void aboutToCollapse();
    void wasExpanded();
    void wasCollapsed();
    void itemClicked(int index);

public slots:
    void collapse();
    void expand();
    void menuItemClicked();

protected slots:
    void setOpaque();

protected:
    const QScopedPointer<QtMaterialCollapsibleMenuPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialCollapsibleMenu)
    Q_DECLARE_PRIVATE(QtMaterialCollapsibleMenu)
};

#endif // QTMATERIALCOLLAPSIBLEMENU_H
