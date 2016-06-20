#ifndef DIALOG_INTERNAL_H
#define DIALOG_INTERNAL_H

#include <QWidget>

class Dialog;

class DialogWindow : public QWidget
{
    Q_OBJECT

public:
    DialogWindow(QWidget *parent = 0);
    ~DialogWindow();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(DialogWindow)
};

//#include <QWidget>
//
//class Dialog;
//
//class DialogProxy : public QWidget
//{
//    Q_OBJECT
//
//public:
//    DialogProxy(Dialog *dialog, QWidget *widget);
//    ~DialogProxy();
//
//protected:
//    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
//
//private:
//    Q_DISABLE_COPY(DialogProxy)
//
//    Dialog *const dialog;
//    QWidget *widget;
//};
//
///* -- */
//
//class DialogWindow : public QWidget
//{
//    Q_OBJECT
//
//public:
//    DialogWindow(Dialog *dialog);
//    ~DialogWindow();
//
//protected:
//    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
//
//private:
//    Q_DISABLE_COPY(DialogWindow)
//
//    Dialog *const dialog;
//};
//
//class DialogShadow : public QWidget
//{
//    Q_OBJECT
//
//public:
//    DialogShadow(QWidget *dialog);
//    ~DialogShadow();
//
//    void setWindow(DialogWindow *window);
//
//protected:
//    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
//    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
//
//private:
//    Q_DISABLE_COPY(DialogShadow)
//
//    DialogWindow *window;
//};

#endif // DIALOG_INTERNAL_H
