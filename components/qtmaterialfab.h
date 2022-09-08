#ifndef QTMATERIALFAB_H
#define QTMATERIALFAB_H

#include "qtmaterialflatbutton.h"

class QtMaterialFloatingActionButtonPrivate;

class QtMaterialFloatingActionButton : public QtMaterialFlatButton
{
    Q_OBJECT

    Q_PROPERTY(bool mini READ isMini WRITE setMini)
    Q_PROPERTY(Qt::Corner corner READ corner WRITE setCorner)
    Q_PROPERTY(QPoint offset READ offset WRITE setOffset)

public:
    explicit QtMaterialFloatingActionButton(const QIcon &icon, QWidget *parent = nullptr);
    ~QtMaterialFloatingActionButton() override;

    bool isMini() const;
    void setMini(bool state);

    Qt::Corner corner() const;
    void setCorner(Qt::Corner corner);

    QPoint offset() const;
    void setOffset(const QPoint &offset);
    void setOffset(int x, int y);

private:
    Q_DISABLE_COPY(QtMaterialFloatingActionButton)
    Q_DECLARE_PRIVATE(QtMaterialFloatingActionButton)

    // QWidget
public:
    QSize sizeHint() const override;

protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void updateClipPath() override;
};

#endif  // QTMATERIALFAB_H
