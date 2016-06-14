#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QLineEdit>

class TextFieldPrivate;

class TextField : public QLineEdit
{
    Q_OBJECT

public:
    explicit TextField(QWidget *parent = 0);
    ~TextField();

protected:
    const QScopedPointer<TextFieldPrivate> d_ptr;

private:
    Q_DISABLE_COPY(TextField)
    Q_DECLARE_PRIVATE(TextField)
};

//#include <QLineEdit>
//
//class QPropertyAnimation;
//
//class TextField : public QLineEdit
//{
//    Q_OBJECT
//
//    Q_PROPERTY(qreal progress WRITE setProgress READ progress NOTIFY progressChanged)
//
//public:
//    explicit TextField(QWidget *parent = 0);
//    ~TextField();
//
//    void setProgress(qreal progress);
//    inline qreal progress() const { return _progress; }
//
//signals:
//    void progressChanged(qreal);
//
//protected:
//    void focusInEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
//    void focusOutEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
//    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
//
//private:
//    QPropertyAnimation *const _animation;
//    qreal                     _progress;
//};

#endif // TEXTFIELD_H
