#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <QAbstractButton>

class RadioButtonPrivate;

class RadioButton : public QAbstractButton
{
    Q_OBJECT

public:
    explicit RadioButton(QWidget *parent = 0);
    ~RadioButton();

    void setUseThemeColors(bool state);
    bool useThemeColors() const;

    void setCheckedColor(const QColor &color);
    QColor checkedColor() const;

    void setUncheckedColor(const QColor &color);
    QColor uncheckedColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

    void setCheckedIcon(const QIcon &icon);
    QIcon checkedIcon() const;

    void setUncheckedIcon(const QIcon &icon);
    QIcon uncheckedIcon() const;

    void setIconSize(int size);
    int iconSize() const;

    QSize sizeHint() const;

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<RadioButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(RadioButton)
    Q_DECLARE_PRIVATE(RadioButton)
};

#endif // RADIOBUTTON_H
