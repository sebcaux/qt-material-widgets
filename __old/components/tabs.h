#ifndef TABS_H
#define TABS_H

#include <QWidget>
#include "lib/theme.h"

class TabsPrivate;
class Tab;

class Tabs : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor inkColor WRITE setInkColor READ inkColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)

public:
    explicit Tabs(QWidget *parent = 0);
    ~Tabs();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setShowHalo(bool state);
    bool showHalo() const;

    void setRippleStyle(Material::RippleStyle style);
    Material::RippleStyle rippleStyle() const;

    void setInkColor(const QColor &color);
    QColor inkColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void addTab(const QString &text);
    void addTab(const QString &text, const QIcon &icon);

    const QLayout *tabLayout() const;
    int currentIndex() const;

signals:
    void currentChanged(int);

protected:
    void moveEvent(QMoveEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<TabsPrivate> d_ptr;

private slots:
    void switchTab();

private:
    Q_DISABLE_COPY(Tabs)
    Q_DECLARE_PRIVATE(Tabs)

    Tab *createTab(const QString &text);
};

#endif // TABS_H
