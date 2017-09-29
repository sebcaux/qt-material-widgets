#ifndef ABOUT_H
#define ABOUT_H

#include <QLabel>

class About : public QLabel
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();
};

#endif // ABOUT_H
