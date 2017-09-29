#ifndef QTMATERIALCOLLAPSIBLEMENU_P_H
#define QTMATERIALCOLLAPSIBLEMENU_P_H

#include <QtGlobal>

class QScrollArea;
class QWidget;
class QVBoxLayout;
class QStackedLayout;
class QtMaterialCollapsibleMenu;
class QtMaterialCollapsibleMenuStateMachine;
class QtMaterialCollapsibleMenuProxy;

class QtMaterialCollapsibleMenuPrivate
{
    Q_DISABLE_COPY(QtMaterialCollapsibleMenuPrivate)
    Q_DECLARE_PUBLIC(QtMaterialCollapsibleMenu)

public:
    QtMaterialCollapsibleMenuPrivate(QtMaterialCollapsibleMenu *q);
    ~QtMaterialCollapsibleMenuPrivate();

    void init();

    QtMaterialCollapsibleMenu             *const q_ptr;
    QScrollArea                           *scrollArea;
    QWidget                               *mainWidget;
    QVBoxLayout                           *menuLayout;
    QtMaterialCollapsibleMenuProxy        *proxy;
    QtMaterialCollapsibleMenuStateMachine *stateMachine;
    QStackedLayout                        *proxyStack;
};

#endif // QTMATERIALCOLLAPSIBLEMENU_P_H
