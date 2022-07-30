#ifndef APPBARSETTINGSEDITOR_H
#define APPBARSETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_appbarsettingsform.h"
#include <QWidget>

class QtMaterialAppBar;

class AppBarSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit AppBarSettingsEditor(QWidget *parent = 0);
    ~AppBarSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::AppBarSettingsForm *const ui;
    QtMaterialAppBar *const m_appBar;
};

#endif  // APPBARSETTINGSEDITOR_H
