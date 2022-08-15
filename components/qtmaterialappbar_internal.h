#ifndef QTMATERIALAPPBARLAYOUT_H
#define QTMATERIALAPPBARLAYOUT_H

#include <QLayout>

#include <QLabel>

#include "qtmaterialiconbutton.h"

class QtMaterialAppBarLayout : public QLayout
{
    Q_DISABLE_COPY(QtMaterialAppBarLayout)

public:
    QtMaterialAppBarLayout(QWidget *parent = nullptr);
    ~QtMaterialAppBarLayout();

    QLabel *titleLabel() const;
    void setTitleLabel(QLabel *titleLabel);
    QtMaterialIconButton *navButton() const;
    void setNavButton(QtMaterialIconButton *navButton);

protected:
    QtMaterialIconButton *_navButton;
    QLabel *_titleLabel;

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
};

#endif  // QTMATERIALAPPBARLAYOUT_H
