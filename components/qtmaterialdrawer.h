#ifndef QTMATERIALDRAWER_H
#define QTMATERIALDRAWER_H

#include "lib/qtmaterialoverlaywidget.h"

class QtMaterialDrawerPrivate;
class QtMaterialDrawerStateMachine;

class QtMaterialDrawer : public QtMaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(bool clickOutsideToClose READ clickOutsideToClose WRITE setClickOutsideToClose)
    Q_PROPERTY(bool autoRaise READ autoRaise WRITE setAutoRaise)
    Q_PROPERTY(bool overlayMode READ overlayMode WRITE setOverlayMode)

public:
    explicit QtMaterialDrawer(QWidget *parent = nullptr);
    ~QtMaterialDrawer() override;

    int drawerWidth() const;
    void setDrawerWidth(int width);

    QLayout *drawerLayout() const;
    void setDrawerLayout(QLayout *layout);

    bool clickOutsideToClose() const;
    void setClickOutsideToClose(bool state);

    bool autoRaise() const;
    void setAutoRaise(bool state);

    bool overlayMode() const;
    void setOverlayMode(bool value);

public slots:
    void openDrawer();
    void closeDrawer();

protected:
    const QScopedPointer<QtMaterialDrawerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialDrawer)
    Q_DECLARE_PRIVATE(QtMaterialDrawer)

    // QWidget interface
protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALDRAWER_H
