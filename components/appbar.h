#ifndef APPBAR_H
#define APPBAR_H

#include <QWidget>

class AppBar : public QWidget
{
    Q_OBJECT

public:
    explicit AppBar(QWidget *parent = 0);
    ~AppBar();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};

#endif // APPBAR_H
