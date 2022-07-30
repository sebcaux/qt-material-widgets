#ifndef SNACKBARSETTINGSEDITOR_H
#define SNACKBARSETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_snackbarsettingsform.h"

class QtMaterialSnackbar;

class SnackbarSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit SnackbarSettingsEditor(QWidget *parent = nullptr);
    ~SnackbarSettingsEditor() override;

protected slots:
    void setupForm();
    void updateWidget();
    void showSnackbar();

private:
    Ui::SnackbarSettingsForm *const ui;
    QtMaterialSnackbar *const m_snackbar;
};

#endif  // SNACKBARSETTINGSEDITOR_H
