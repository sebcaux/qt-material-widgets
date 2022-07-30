#ifndef AUTOCOMPLETESETTINGSEDITOR_H
#define AUTOCOMPLETESETTINGSEDITOR_H

#include "settingseditor.h"

#include "lib/qtmaterialoverlaywidget.h"

class QtMaterialAutoComplete;

class AutoCompleteSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit AutoCompleteSettingsEditor(QWidget *parent = 0);
    ~AutoCompleteSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    QtMaterialAutoComplete *const m_autocomplete;
};

#endif  // AUTOCOMPLETESETTINGSEDITOR_H
