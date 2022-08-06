#ifndef QTMATERIALRADIOBUTTON_H
#define QTMATERIALRADIOBUTTON_H

#include "lib/qtmaterialcheckable.h"

class QtMaterialRadioButtonPrivate;

class QtMaterialRadioButton : public QtMaterialCheckable
{
    Q_OBJECT

public:
    explicit QtMaterialRadioButton(QWidget *parent = nullptr);
    explicit QtMaterialRadioButton(const QString &text, QWidget *parent = nullptr);
    ~QtMaterialRadioButton() override;

protected:
    void setupProperties() override;

private:
    Q_DISABLE_COPY(QtMaterialRadioButton)
    Q_DECLARE_PRIVATE(QtMaterialRadioButton)
};

#endif  // QTMATERIALRADIOBUTTON_H
