#ifndef QTMATERIALTABS_INTERNAL_H
#define QTMATERIALTABS_INTERNAL_H

#include "lib/qtmaterialoverlaywidget.h"

#include "qtmaterialflatbutton.h"

class QPropertyAnimation;
class QtMaterialTabs;

class QtMaterialTabsInkBar : public QtMaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal tweenValue WRITE setTweenValue READ tweenValue)

public:
    QtMaterialTabsInkBar(QtMaterialTabs *parent);
    ~QtMaterialTabsInkBar() override;

    inline void setTweenValue(qreal value);
    inline qreal tweenValue() const;

    void refreshGeometry();
    void animate();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(QtMaterialTabsInkBar)

    QtMaterialTabs *const m_tabs;
    QPropertyAnimation *const m_animation;
    QRect m_geometry;
    QRect m_previousGeometry;
    qreal m_tween;
};

inline void QtMaterialTabsInkBar::setTweenValue(qreal value)
{
    m_tween = value;
    refreshGeometry();
}

inline qreal QtMaterialTabsInkBar::tweenValue() const
{
    return m_tween;
}

class QtMaterialTab : public QtMaterialFlatButton
{
    Q_OBJECT

public:
    explicit QtMaterialTab(QtMaterialTabs *parent);
    ~QtMaterialTab() override;

    inline void setActive(bool state);
    inline bool isActive() const;

    QSize sizeHint() const override;

protected:
    void paintForeground(QPainter *painter) override;

private:
    Q_DISABLE_COPY(QtMaterialTab)

    QtMaterialTabs *const m_tabs;
    bool m_active;
};

inline void QtMaterialTab::setActive(bool state)
{
    m_active = state;
    update();
}

inline bool QtMaterialTab::isActive() const
{
    return m_active;
}

#endif  // QTMATERIALTABS_INTERNAL_H
