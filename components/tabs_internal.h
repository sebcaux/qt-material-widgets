#ifndef TABS_INTERNAL_H
#define TABS_INTERNAL_H

#include <QObject>
#include "flatbutton.h"

class QPropertyAnimation;
class Tabs;

class TabsDelegate : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal tween WRITE setTween READ tween)

public:
    TabsDelegate(Tabs *parent);
    ~TabsDelegate();

    void setTween(qreal tween);
    inline qreal tween() const { return _tween; }

    void setInkBarGeometry(const QRect &newGeometry);
    inline QRect inkBarGeometry() const { return _inkBarGeometry; }
    \
    void updateInkBar();

private:
    Q_DISABLE_COPY(TabsDelegate)

    Tabs *const tabs;
    QPropertyAnimation *_animation;
    qreal _tween;
    QRect _inkBarGeometry;
    QRect _previousGeometry;
};

class Tab : public FlatButton
{
    Q_OBJECT

public:
    explicit Tab(QWidget *parent = 0);
    explicit Tab(QString text, QWidget *parent = 0);
    ~Tab();

private:
    Q_DISABLE_COPY(Tab)

    void init();
};

#endif // TABS_INTERNAL_H
