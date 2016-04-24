#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QAbstractButton>

class QStyleOptionButton;

class Checkbox : public QAbstractButton
{
    Q_OBJECT

public:
    explicit Checkbox(QWidget *parent = 0);
    ~Checkbox();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    void initStyleOption(QStyleOptionButton *option) const;
};

#endif // CHECKBOX_H
