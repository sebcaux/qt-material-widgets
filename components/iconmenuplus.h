#ifndef ICONMENUPLUS_H
#define ICONMENUPLUS_H

#include "xx/qtmaterialiconbutton.h"

class QtMaterialOverlayWidget;
//class MenuPlus;
class QtMaterialCollapsibleMenu;
class QtMaterialMenuItem;

class IconMenuPlus : public QtMaterialIconButton
{
    Q_OBJECT

public:
    explicit IconMenuPlus(const QIcon &icon, QWidget *parent = 0);
    ~IconMenuPlus();

    void addMenuItem(const QString &text);
    void addMenuItem(QtMaterialMenuItem *item);

protected slots:
    void xxx();
    void yyy();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(IconMenuPlus)
//    Q_DECLARE_PRIVATE(IconMenuPlus)

    QtMaterialOverlayWidget   *menuOverlay;
    QtMaterialCollapsibleMenu *menu;
};

#endif // ICONMENUPLUS_H
