#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QLineEdit>

class TextField : public QLineEdit
{
    Q_OBJECT

public:
    explicit TextField(QWidget *parent = 0);
    ~TextField();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};

#endif // TEXTFIELD_H
