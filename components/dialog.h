#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>

class DialogPrivate;

class Dialog : public QWidget
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    QLayout *windowLayout() const;
    void setWindowLayout(QLayout *layout);

protected slots:
    void pressOne();
    void pressTwo();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<DialogPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Dialog)
    Q_DECLARE_PRIVATE(Dialog)
};

//    //QWidget *dialogWidget() const;
//
//protected slots:
//    void pressOne();
//    void pressTwo();
//
//protected:
////    bool event(QEvent *event) Q_DECL_OVERRIDE;
////    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
//    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
//
//    const QScopedPointer<DialogPrivate> d_ptr;
//
//private:
//    Q_DISABLE_COPY(Dialog)
//    Q_DECLARE_PRIVATE(Dialog)
//};

#endif // DIALOG_H
