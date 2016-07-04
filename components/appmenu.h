#ifndef APPMENU_H
#define APPMENU_H

#include <QMenu>

class Menu;
class SizeProxyWidget;

class AppMenu : public QMenu
{
    Q_OBJECT

public:
    explicit AppMenu(QWidget *parent = 0);
    explicit AppMenu(const QString &title, QWidget *parent = 0);
    ~AppMenu();

    //QSize sizeHint() const;

protected slots:
    void animateExpand();

protected:
    //bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

    //void actionEvent(QActionEvent *event) Q_DECL_OVERRIDE;
    //void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void actionEvent(QActionEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(AppMenu)
    //Q_DECLARE_PRIVATE(AppMenu)

    //QHash<QAction *, FlatButton *> menuItems;

    void init();

    Menu            *_menu;
    SizeProxyWidget *_proxyWidget;
};

#endif // APPMENU_H
