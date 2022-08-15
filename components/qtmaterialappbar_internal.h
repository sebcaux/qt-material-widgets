#ifndef QTMATERIALAPPBARLAYOUT_H
#define QTMATERIALAPPBARLAYOUT_H

#include <QLayout>

#include <QLabel>

class QtMaterialAppBar;
class QtMaterialIconButton;

class QtMaterialAppBarLayoutItem : public QWidgetItem
{
public:
    QtMaterialAppBarLayoutItem(QWidget *widget);
    bool isEmpty() const override;

    QAction *action;
};

class QtMaterialAppBarLayout : public QLayout
{
    Q_DISABLE_COPY(QtMaterialAppBarLayout)

public:
    QtMaterialAppBarLayout(QtMaterialAppBar *parent = nullptr);
    ~QtMaterialAppBarLayout();

    QLabel *titleLabel() const;
    void setTitleLabel(QLabel *titleLabel);
    QtMaterialIconButton *navButton() const;
    void setNavButton(QtMaterialIconButton *navButton);

    void insertAction(int index, QAction *action);

    void updateActions();

protected:
    QtMaterialIconButton *_navButton;
    QLabel *_titleLabel;
    QList<QtMaterialAppBarLayoutItem *> _actionIconButtons;

    // QLayoutItem interface
public:
    QSize sizeHint() const override;

    // QLayout interface
public:
    void addItem(QLayoutItem *) override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;
    int count() const override;
    QSize minimumSize() const override;
    QSize maximumSize() const override;
    Qt::Orientations expandingDirections() const override;
    void setGeometry(const QRect &) override;
    const QList<QtMaterialAppBarLayoutItem *> &actionIconButtons() const;
};

#endif  // QTMATERIALAPPBARLAYOUT_H
