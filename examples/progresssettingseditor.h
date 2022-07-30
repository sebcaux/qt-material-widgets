#ifndef PROGRESSSETTINGSEDITOR_H
#define PROGRESSSETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_progresssettingsform.h"

class QtMaterialProgress;

class ProgressSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit ProgressSettingsEditor(QWidget *parent = nullptr);
    ~ProgressSettingsEditor() override;

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::ProgressSettingsForm *const ui;
    QtMaterialProgress *const m_progress;
};

#endif  // PROGRESSSETTINGSEDITOR_H
