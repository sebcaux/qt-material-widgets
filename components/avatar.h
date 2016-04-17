#ifndef AVATAR_H
#define AVATAR_H

#include <QWidget>

class Avatar : public QWidget
{
    Q_OBJECT

public:
    explicit Avatar(QWidget *parent = 0);
    ~Avatar();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};

#endif // AVATAR_H
