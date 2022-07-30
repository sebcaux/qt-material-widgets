#ifndef MENUSETTINGSEDITOR_H
#define MENUSETTINGSEDITOR_H

#include "settingseditor.h"

#include "lib/qtmaterialoverlaywidget.h"

class QtMaterialMenu;

class MenuSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit MenuSettingsEditor(QWidget *parent = nullptr);
    ~MenuSettingsEditor() override;

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    QtMaterialMenu *const m_menu;
};

#endif  // MENUSETTINGSEDITOR_H
