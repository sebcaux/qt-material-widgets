#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QLineEdit>

class TextFieldPrivate;

class TextField : public QLineEdit
{
    Q_OBJECT

    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor inkColor WRITE setInkColor READ inkColor)
    Q_PROPERTY(QColor underlineColor WRITE setUnderlineColor READ underlineColor)
    Q_PROPERTY(QColor hintColor WRITE setHintColor READ hintColor)

public:
    explicit TextField(QWidget *parent = 0);
    ~TextField();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setShowLabel(bool value);
    bool hasLabel() const;

    void setLabelFontSize(qreal size);
    qreal labelFontSize() const;

    void setLabel(const QString &label);
    QString label() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setInkColor(const QColor &color);
    QColor inkColor() const;

    void setUnderlineColor(const QColor &color);
    QColor underlineColor() const;

    void setHintColor(const QColor &color);
    QColor hintColor() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<TextFieldPrivate> d_ptr;

private:
    Q_DISABLE_COPY(TextField)
    Q_DECLARE_PRIVATE(TextField)
};

#endif // TEXTFIELD_H
