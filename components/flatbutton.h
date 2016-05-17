#ifndef FLATBUTTON_H
#define FLATBUTTON_H

#include <QPushButton>
#include <QScopedPointer>
#include "lib/theme.h"

class FlatButtonPrivate;

class FlatButton : public QPushButton
{
    Q_OBJECT

public:
    explicit FlatButton(QWidget *parent = 0);
    explicit FlatButton(const QString &text, QWidget *parent = 0);
    ~FlatButton();

    void setRole(Material::Role role);

protected:
    FlatButton(FlatButtonPrivate &d, QWidget *parent = 0);

    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<FlatButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(FlatButton)
    Q_DECLARE_PRIVATE(FlatButton)
};

#endif // FLATBUTTON_H
