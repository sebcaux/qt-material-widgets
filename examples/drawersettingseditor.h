#ifndef DRAWERSETTINGSEDITOR_H
#define DRAWERSETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_drawersettingsform.h"

class QtMaterialDrawer;

class DrawerSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit DrawerSettingsEditor(QWidget *parent = nullptr);
    ~DrawerSettingsEditor() override;

protected slots:
    void setupForm();
    void updateWidget();

private:
    Ui::DrawerSettingsForm *const ui;
    QtMaterialDrawer *const m_drawer;
};

#endif  // DRAWERSETTINGSEDITOR_H
