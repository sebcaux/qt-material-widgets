#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QLineEdit>

class TextFieldPrivate;

class TextField : public QLineEdit
{
    Q_OBJECT

    Q_PROPERTY(QColor textColor WRITE setTextColor READ progress NOTIFY textColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ progress NOTIFY backgroundColor)
    Q_PROPERTY(QColor inkColor WRITE setInkColor READ progress NOTIFY inkColor)
    Q_PROPERTY(QColor underlineColor WRITE setUnderlineColor READ progress NOTIFY underlineColor)

public:
    explicit TextField(QWidget *parent = 0);
    ~TextField();

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setInkColor(const QColor &color);
    QColor inkColor() const;

    void setUnderlineColor(const QColor &color);
    QColor underlineColor() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<TextFieldPrivate> d_ptr;

private:
    Q_DISABLE_COPY(TextField)
    Q_DECLARE_PRIVATE(TextField)
};

#endif // TEXTFIELD_H
