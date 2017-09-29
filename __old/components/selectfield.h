#ifndef SELECTFIELD_H
#define SELECTFIELD_H

#include <QWidget>

class SelectField : public QWidget
{
    Q_OBJECT

public:
    explicit SelectField(QWidget *parent = 0);
    ~SelectField();

private:
    Q_DISABLE_COPY(SelectField)
    //Q_DECLARE_PRIVATE(SelectField)
};

#endif // SELECTFIELD_H
