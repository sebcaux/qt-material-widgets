#ifndef DRAWER_H
#define DRAWER_H

#include "lib/overlaywidget.h"

class DrawerPrivate;
class DrawerStateMachine;

class Drawer : public OverlayWidget
{
    Q_OBJECT

public:
    explicit Drawer(QWidget *parent = 0);
    ~Drawer();

    void setDrawerWidth(int width);
    int drawerWidth() const;

    void setDrawerLayout(QLayout *layout);
    QLayout *drawerLayout() const;

protected slots:
    void openDrawer();
    void closeDrawer();

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    QRect overlayGeometry() const Q_DECL_OVERRIDE;

    const QScopedPointer<DrawerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Drawer)
    Q_DECLARE_PRIVATE(Drawer)
};

#endif // DRAWER_H
