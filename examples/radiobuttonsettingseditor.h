#ifndef RADIOBUTTONSETTINGSEDITOR_H
#define RADIOBUTTONSETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_radiobuttonsettingsform.h"

class QtMaterialRadioButton;
class RadioButton;

class RadioButtonSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit RadioButtonSettingsEditor(QWidget *parent = 0);
    ~RadioButtonSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::RadioButtonSettingsForm *const ui;
    QtMaterialRadioButton *const m_radioButton1;
    QtMaterialRadioButton *const m_radioButton2;
    QtMaterialRadioButton *const m_radioButton3;
};

#endif  // RADIOBUTTONSETTINGSEDITOR_H
