#ifndef QTMATERIALCHECKBOX_H
#define QTMATERIALCHECKBOX_H

#include "qtmaterialwidgets.h"

#include "lib/qtmaterialcheckable.h"

class QtMaterialCheckBoxPrivate;

class QTMATERIALWIDGETS_EXPORT QtMaterialCheckBox : public QtMaterialCheckable
{
    Q_OBJECT

public:
    explicit QtMaterialCheckBox(QWidget *parent = nullptr);
    explicit QtMaterialCheckBox(const QString &text, QWidget *parent = nullptr);
    ~QtMaterialCheckBox() override;

private:
    Q_DISABLE_COPY(QtMaterialCheckBox)
    Q_DECLARE_PRIVATE(QtMaterialCheckBox)
};

#endif  // QTMATERIALCHECKBOX_H
