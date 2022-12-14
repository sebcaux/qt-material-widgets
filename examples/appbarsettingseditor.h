#ifndef APPBARSETTINGSEDITOR_H
#define APPBARSETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_appbarsettingsform.h"

class QtMaterialAppBar;

class AppBarSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit AppBarSettingsEditor(QWidget *parent = nullptr);
    ~AppBarSettingsEditor() override;

protected slots:
    void setupForm() override;
    void updateWidget() override;
    void selectColor();

private:
    Ui::AppBarSettingsForm *const ui;
    QtMaterialAppBar *const m_appBar;
};

#endif  // APPBARSETTINGSEDITOR_H
