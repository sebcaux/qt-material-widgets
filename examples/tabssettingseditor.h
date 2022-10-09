#ifndef TABSSETTINGSEDITOR_H
#define TABSSETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_tabssettingsform.h"

class QtMaterialTabs;

class TabsSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit TabsSettingsEditor(QWidget *parent = nullptr);
    ~TabsSettingsEditor() override;

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::TabsSettingsForm *const ui;
    QtMaterialTabs *const m_tabs;
};

#endif  // TABSSETTINGSEDITOR_H
