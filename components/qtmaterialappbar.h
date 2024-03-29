#ifndef QTMATERIALAPPBAR_H
#define QTMATERIALAPPBAR_H

#include "qtmaterialwidgets.h"

#include <QWidget>

#include "lib/qtmaterialtheme.h"

class QtMaterialAppBarPrivate;

class QTMATERIALWIDGETS_EXPORT QtMaterialAppBar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(Material::NavIconType navIconType READ navIconType WRITE setNavIconType)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    explicit QtMaterialAppBar(const QString &title, QWidget *parent = nullptr);
    explicit QtMaterialAppBar(QWidget *parent = nullptr);
    ~QtMaterialAppBar() override;

    const QString &title() const;
    void setTitle(const QString &title);

    Material::NavIconType navIconType() const;
    void setNavIconType(Material::NavIconType navIconType);

    const QSize &iconSize() const;
    void setIconSize(const QSize &iconSize);
    void setIconSize(int w, int h);

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor foregroundColor() const;
    void setForegroundColor(const QColor &color);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

signals:
    void navIconClicked();

protected:
    const QScopedPointer<QtMaterialAppBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialAppBar)
    Q_DECLARE_PRIVATE(QtMaterialAppBar)

    // QWidget interface
protected:
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void actionEvent(QActionEvent *event) override;
};

#endif  // QTMATERIALAPPBAR_H
