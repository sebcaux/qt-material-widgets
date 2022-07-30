#ifndef CHECKBOXSETTINGSEDITOR_H
#define CHECKBOXSETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_checkboxsettingsform.h"

class QtMaterialCheckable;

class CheckBoxSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit CheckBoxSettingsEditor(QWidget *parent = nullptr);
    ~CheckBoxSettingsEditor() override;

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::CheckBoxSettingsForm *const ui;
    QtMaterialCheckable *const m_checkBox;
};

#endif  // CHECKBOXSETTINGSEDITOR_H
