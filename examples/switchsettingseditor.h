#ifndef SWITCHSETTINGSEDITOR_H
#define SWITCHSETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_switchsettingsform.h"

class QtMaterialSwitch;

class SwitchSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit SwitchSettingsEditor(QWidget *parent = nullptr);
    ~SwitchSettingsEditor() override;

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::SwitchSettingsForm *const ui;
    QtMaterialSwitch *const m_switch;
};

#endif  // SWITCHSETTINGSEDITOR_H
