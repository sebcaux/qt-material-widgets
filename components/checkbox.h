#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QWidget>

class Checkbox : public QWidget
{
    Q_OBJECT

public:
    explicit Checkbox(QWidget *parent = 0);
    ~Checkbox();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};

#endif // CHECKBOX_H
