#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <QRadioButton>

class RadioButtonPrivate;

class RadioButton : public QRadioButton
{
    Q_OBJECT

public:
    explicit RadioButton(QWidget *parent = 0);
    ~RadioButton();

    QSize sizeHint() const;

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<RadioButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(RadioButton)
    Q_DECLARE_PRIVATE(RadioButton)
};

#endif // RADIOBUTTON_H
