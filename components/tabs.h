#ifndef TABS_H
#define TABS_H

#include <QWidget>
#include "lib/theme.h"

class TabsPrivate;

class Tabs : public QWidget
{
    Q_OBJECT

public:
    explicit Tabs(QWidget *parent = 0);
    ~Tabs();

    void addTab(const QString &text);

    void setRippleStyle(Material::RippleStyle style);

    const QLayout *tabLayout() const;
    int currentIndex() const;

signals:
    void currentChanged(int);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void moveEvent(QMoveEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<TabsPrivate> d_ptr;

private slots:
    void switchTab();

private:
    Q_DISABLE_COPY(Tabs)
    Q_DECLARE_PRIVATE(Tabs)
};

#endif // TABS_H
