#ifndef TABS_INTERNAL_H
#define TABS_INTERNAL_H

#include <QObject>
#include "flatbutton.h"

class Tabs;
class QPropertyAnimation;

class TabsInkBar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal tweenValue WRITE setTweenValue READ tweenValue)

public:
    TabsInkBar(Tabs *parent);
    ~TabsInkBar();

    void setTweenValue(qreal value);
    inline qreal tweenValue() const { return _tween; }

    void refreshGeometry();
    void animate();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Q_DISABLE_COPY(TabsInkBar)

    Tabs               *const tabs;
    QPropertyAnimation *_animation;
    qreal               _tween;
    QRect               _previousGeometry;
};

class Tab : public FlatButton
{
    Q_OBJECT

public:
    explicit Tab(QWidget *parent = 0);
    explicit Tab(QString text, QWidget *parent = 0);
    ~Tab();

    inline void setActive(bool state) { _active = state; update(); }
    inline bool isActive() const { return _active; }

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(Tab)

    void init();

    bool _active;
};

#endif // TABS_INTERNAL_H
