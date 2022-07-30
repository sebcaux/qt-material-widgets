#ifndef QTMATERIALRAISEDBUTTON_H
#define QTMATERIALRAISEDBUTTON_H

#include "qtmaterialflatbutton.h"

class QtMaterialRaisedButtonPrivate;

class QtMaterialRaisedButton : public QtMaterialFlatButton
{
    Q_OBJECT

public:
    explicit QtMaterialRaisedButton(QWidget *parent = nullptr);
    explicit QtMaterialRaisedButton(const QString &text, QWidget *parent = nullptr);
    ~QtMaterialRaisedButton() override;

protected:
    QtMaterialRaisedButton(QtMaterialRaisedButtonPrivate &d, QWidget *parent = nullptr);

    bool event(QEvent *event) override;

private:
    Q_DISABLE_COPY(QtMaterialRaisedButton)
    Q_DECLARE_PRIVATE(QtMaterialRaisedButton)
};

#endif  // QTMATERIALRAISEDBUTTON_H
