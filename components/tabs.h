#ifndef TABS_H
#define TABS_H

#include <QWidget>

class QHBoxLayout;
class QPropertyAnimation;
class Tab;

class Tabs : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal tween WRITE setTween READ tween)

public:
    explicit Tabs(QWidget *parent = 0);
    ~Tabs();

    inline void setTween(qreal tween) { _tween = tween; updateInkBar(); }
    inline qreal tween() const { return _tween; }

    void addTab(Tab *tab);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void moveEvent(QMoveEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

protected slots:
    void switchActiveTab();

signals:
    void currentChanged(int);

private:
    void updateInkBar();

    QHBoxLayout        *const _tabLayout;
    QPropertyAnimation *const _animation;
    QRect                     _inkBarGeometry;
    QRect                     _previousGeometry;
    int                       _tab;
    qreal                     _tween;
};

#endif // TABS_H
