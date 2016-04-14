#ifndef LIST_H
#define LIST_H

#include <QWidget>

class List : public QWidget
{
    Q_OBJECT

public:
    explicit List(QWidget *parent = 0);
    ~List();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};

#endif // LIST_H
