#ifndef SELECTFIELDPLUS_H
#define SELECTFIELDPLUS_H

#include <QWidget>

class QtMaterialOverlayWidget;
class QtMaterialCollapsibleMenu;
class QtMaterialMenuItem;

class SelectFieldPlus : public QWidget
{
    Q_OBJECT

public:
    explicit SelectFieldPlus(QWidget *parent = 0);
    ~SelectFieldPlus();

    QSize sizeHint() const;

    QColor underlineColor() const;

signals:
    void itemSelected(int index);

public slots:
    void setSelectedIndex(int index);

protected slots:
    void makeTransparent();
    void makeOpaque();
    void collapseDelayed();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(SelectFieldPlus)

    QtMaterialOverlayWidget   *_menuOverlay;
    QtMaterialCollapsibleMenu *_menu;
    int                        _selectedIndex;
    QString                    _selectedText;
};

#endif // SELECTFIELDPLUS_H
