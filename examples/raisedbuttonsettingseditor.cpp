#include "raisedbuttonsettingseditor.h"

#include <qtmaterialraisedbutton.h>

RaisedButtonSettingsEditor::RaisedButtonSettingsEditor(QWidget *parent)
    : FlatButtonSettingsEditor(new QtMaterialRaisedButton("Rise up"), parent)
{
}

RaisedButtonSettingsEditor::~RaisedButtonSettingsEditor()
{
}
