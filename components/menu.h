#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "flatbutton.h"

class MenuItem : public FlatButton
{
    Q_OBJECT

public:
    explicit MenuItem(QWidget *parent = 0);
    explicit MenuItem(const QString &text, QWidget *parent = 0);
    ~MenuItem();

    QSize sizeHint() const Q_DECL_OVERRIDE;
};

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

    void addMenuItem(MenuItem *item);
    void addMenuItem(const QString &text);

    inline int itemCount() const { return m_items.count(); }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QList<MenuItem *> m_items;
};

#endif // MENU_H
