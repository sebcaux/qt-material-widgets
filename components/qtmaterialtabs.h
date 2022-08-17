#ifndef QTMATERIALTABS_H
#define QTMATERIALTABS_H

#include <QWidget>

#include "lib/qtmaterialtheme.h"

#include <QIcon>

class QtMaterialTabsPrivate;
class QtMaterialTab;
class QTabbar;

class QtMaterialTabs : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentChanged)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(QColor inkColor READ inkColor WRITE setInkColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

public:
    explicit QtMaterialTabs(QWidget *parent = nullptr);
    ~QtMaterialTabs() override;

    void addTab(const QString &text, const QIcon &icon = QIcon());
    void setCurrentIndex(int index);
    int currentIndex() const;
    int count() const;

    const QSize &iconSize() const;
    void setIconSize(const QSize &iconSize);
    void setIconSize(int w, int h);

    bool isHaloVisible() const;
    void setHaloVisible(bool value);

    Material::RippleStyle rippleStyle() const;
    void setRippleStyle(Material::RippleStyle style);

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor inkColor() const;
    void setInkColor(const QColor &color);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);
    QColor textColor() const;
    void setTextColor(const QColor &color);

signals:
    void currentChanged(int);

protected:
    void setTabActive(int index, bool active = true);
    void updateTabs();

    const QScopedPointer<QtMaterialTabsPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialTabs)
    Q_DECLARE_PRIVATE(QtMaterialTabs)
};

#endif  // QTMATERIALTABS_H
