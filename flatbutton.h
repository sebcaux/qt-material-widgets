#ifndef FLATBUTTON_H
#define FLATBUTTON_H

#include <QAbstractButton>

class FlatButton : public QAbstractButton
{
    Q_OBJECT

public:
    explicit FlatButton(QWidget *parent = 0);
    explicit FlatButton(const QString &text, QWidget *parent = 0);
    ~FlatButton();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
};

#endif // FLATBUTTON_H
