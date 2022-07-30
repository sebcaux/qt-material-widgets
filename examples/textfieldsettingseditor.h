#ifndef TEXTFIELDSETTINGSEDITOR_H
#define TEXTFIELDSETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_textfieldsettingsform.h"

class QtMaterialTextField;

class TextFieldSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit TextFieldSettingsEditor(QWidget *parent = 0);
    ~TextFieldSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();
    void setShowInputLine();

private:
    Ui::TextFieldSettingsForm *const ui;
    QtMaterialTextField       *const m_textField;
};

#endif // TEXTFIELDSETTINGSEDITOR_H
