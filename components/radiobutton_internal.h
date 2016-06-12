#ifndef RADIOBUTTON_INTERNAL_H
#define RADIOBUTTON_INTERNAL_H

#include <QWidget>

class RadioButtonIcon : public QWidget
{
    Q_OBJECT

public:
    RadioButtonIcon(QWidget *parent = 0);
    ~RadioButtonIcon();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(RadioButtonIcon)
};

#endif // RADIOBUTTON_INTERNAL_H
