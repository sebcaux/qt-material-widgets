#ifndef MENUPLUS_H
#define MENUPLUS_H

#include <QWidget>

class QStackedLayout;
class QGraphicsDropShadowEffect;
class QStateMachine;
class MenuPlusProxy;
class ScrollBar;

class MenuPlus : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPlus(QWidget *parent = 0);
    ~MenuPlus();

    void addMenuItem(const QString &text);

signals:
    void aboutToExpand();
    void aboutToCollapse();
    void wasExpanded();
    void wasCollapsed();

public slots:
    void collapse();
    void expand();

protected slots:
    void collapseDelayed();
    void setOpaque();

private:
    Q_DISABLE_COPY(MenuPlus)
    //Q_DECLARE_PRIVATE(MenuPlus)

    //friend class MainWindow; // TEMP TEMP TEMP

    QStackedLayout            *_layout;
    QWidget                   *_widget;
    ScrollBar                 *_scrollBar;
    QGraphicsDropShadowEffect *_effect;
    MenuPlusProxy             *_proxy;
    QStateMachine             *_stateMachine;
};

#endif // MENUPLUS_H
