#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "lib/checkable.h"

class CheckBoxPrivate;

class CheckBox : public Checkable
{
    Q_OBJECT

public:
    explicit CheckBox(QWidget *parent = 0);
    ~CheckBox();

protected:
    void assignProperties() Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(CheckBox)
    Q_DECLARE_PRIVATE(CheckBox)
};

#endif // CHECKBOX_H
