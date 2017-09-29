#ifndef QTMATERIALICONMENU_H
#define QTMATERIALICONMENU_H

#include "xx/qtmaterialiconbutton.h"

class QtMaterialIconMenuPrivate;
class QtMaterialMenuItem;

class QtMaterialIconMenu : public QtMaterialIconButton
{
    Q_OBJECT

public:
    explicit QtMaterialIconMenu(const QIcon &icon, QWidget *parent = 0);
    ~QtMaterialIconMenu();

    void addMenuItem(const QString &text);
    void addMenuItem(QtMaterialMenuItem *item);

    QtMaterialMenuItem *itemAt(int index) const;

    void setAutoCollapse(bool value);
    bool autoCollapse() const;

signals:
    void itemSelected(int index);

protected slots:
    void makeTransparent();
    void makeOpaque();
    void collapseDelayed();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialIconMenu)
    Q_DECLARE_PRIVATE(QtMaterialIconMenu)
};

#endif // QTMATERIALICONMENU_H
