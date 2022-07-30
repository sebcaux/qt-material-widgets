#ifndef DIALOGSETTINGSEDITOR_H
#define DIALOGSETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_dialogsettingsform.h"

class QtMaterialDialog;

class DialogSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit DialogSettingsEditor(QWidget *parent = nullptr);
    ~DialogSettingsEditor() override;

protected slots:
    void setupForm();
    void updateWidget();

private:
    Ui::DialogSettingsForm *const ui;
    QtMaterialDialog *const m_dialog;
};

#endif  // DIALOGSETTINGSEDITOR_H
