#ifndef SELECTFIELDSETTINGSEDITOR_H
#define SELECTFIELDSETTINGSEDITOR_H

#include <QWidget>
#include "ui_selectfieldsettingsform.h"

class QtMaterialSelectField;

class SelectFieldSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SelectFieldSettingsEditor(QWidget *parent = 0);
    ~SelectFieldSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::SelectFieldSettingsForm *const ui;
    QtMaterialSelectField       *const m_selectField;
};

#endif // SELECTFIELDSETTINGSEDITOR_H
