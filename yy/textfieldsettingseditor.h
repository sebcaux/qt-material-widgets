#ifndef TEXTFIELDSETTINGSEDITOR_H
#define TEXTFIELDSETTINGSEDITOR_H

#include <QWidget>
#include "ui_textfieldsettingsform.h"

//class TextField;
class QtMaterialTextField;

class TextFieldSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TextFieldSettingsEditor(QWidget *parent = 0);
    ~TextFieldSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::TextFieldSettingsForm *const ui;
    //TextField       *const m_textField;
    QtMaterialTextField       *const m_textField;
};

#endif // TEXTFIELDSETTINGSEDITOR_H
