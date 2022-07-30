#ifndef QTMATERIALFAB_H
#define QTMATERIALFAB_H

#include "qtmaterialraisedbutton.h"

class QtMaterialFloatingActionButtonPrivate;

class QtMaterialFloatingActionButton : public QtMaterialRaisedButton
{
    Q_OBJECT

public:
    explicit QtMaterialFloatingActionButton(const QIcon &icon, QWidget *parent = nullptr);
    ~QtMaterialFloatingActionButton() override;

    QSize sizeHint() const override;

    void setMini(bool state);
    bool isMini() const;

    void setCorner(Qt::Corner corner);
    Qt::Corner corner() const;

    void setOffset(int x, int y);
    QSize offset() const;

    void setXOffset(int x);
    int xOffset() const;

    void setYOffset(int y);
    int yOffset() const;

protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void updateClipPath() override;

private:
    Q_DISABLE_COPY(QtMaterialFloatingActionButton)
    Q_DECLARE_PRIVATE(QtMaterialFloatingActionButton)
};

#endif  // QTMATERIALFAB_H
