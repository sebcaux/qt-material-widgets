#ifndef QTMATERIALAPPBAR_H
#define QTMATERIALAPPBAR_H

#include <QWidget>

#include "lib/qtmaterialtheme.h"

class QtMaterialAppBarPrivate;

class QtMaterialAppBar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(Material::NavIconType navIconType READ navIconType WRITE setNavIconType)
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
public:
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void actionEvent(QActionEvent *event) override;
};

#endif  // QTMATERIALAPPBAR_H
