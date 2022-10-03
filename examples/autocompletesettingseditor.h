#ifndef AUTOCOMPLETESETTINGSEDITOR_H
#define AUTOCOMPLETESETTINGSEDITOR_H

#include "settingseditor.h"

class QtMaterialAutoComplete;

class AutoCompleteSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit AutoCompleteSettingsEditor(QWidget *parent = nullptr);
    ~AutoCompleteSettingsEditor() override;

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    QtMaterialAutoComplete *const m_autocomplete;
};

#endif  // AUTOCOMPLETESETTINGSEDITOR_H
