#ifndef QTMATERIALDRAWER_H
#define QTMATERIALDRAWER_H

#include "lib/qtmaterialoverlaywidget.h"

class QtMaterialDrawerPrivate;
class QtMaterialDrawerStateMachine;

class QtMaterialDrawer : public QtMaterialOverlayWidget
{
    Q_OBJECT

public:
    explicit QtMaterialDrawer(QWidget *parent = nullptr);
    ~QtMaterialDrawer() override;

    void setDrawerWidth(int width);
    int drawerWidth() const;

    void setDrawerLayout(QLayout *layout);
    QLayout *drawerLayout() const;

    void setClickOutsideToClose(bool state);
    bool clickOutsideToClose() const;

    void setAutoRaise(bool state);
    bool autoRaise() const;

    void setOverlayMode(bool value);
    bool overlayMode() const;

public slots:
    void openDrawer();
    void closeDrawer();

protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<QtMaterialDrawerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialDrawer)
    Q_DECLARE_PRIVATE(QtMaterialDrawer)
};

#endif  // QTMATERIALDRAWER_H
