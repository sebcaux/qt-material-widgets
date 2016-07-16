#ifndef ICONMENU_H
#define ICONMENU_H

#include <QWidget>
#include <QPoint>
#include "iconbutton.h"

class QtMaterialOverlayWidget;

class MenuOverlay : public QWidget
{
    Q_OBJECT

public:
    explicit MenuOverlay(QWidget *parent = 0);
    ~MenuOverlay();
};

class QPropertyAnimation;
//class ScaleEffect;
class Menu;

class IconMenu : public IconButton
{
    Q_OBJECT

    Q_PROPERTY(qreal progress WRITE setProgress READ progress NOTIFY progressChanged)

public:
    explicit IconMenu(const QIcon &icon, QWidget *parent = 0);
    ~IconMenu();

    void setProgress(qreal progress);
    inline qreal progress() const { return _progress; }

    void setOverlayParent(QWidget *parent);

protected slots:
    void toggleMenu();
    void animationFinished();

signals:
    void progressChanged(qreal);

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    bool event(QEvent *event) Q_DECL_OVERRIDE;

    void updateOverlayGeometry();

private:
    //MenuOverlay            *const _menuOverlay;
    QtMaterialOverlayWidget *const _menuOverlay;
    Menu                   *const _menu;
    QPropertyAnimation     *const _animation;
    //ScaleEffect        *const _effect;
    QPoint                        _menuPos;
    bool                          _menuVisible;
    qreal                         _progress;
};

#endif // ICONMENU_H
