#ifndef CIRCULARPROGRESSSETTINGSEDITOR_H
#define CIRCULARPROGRESSSETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_circularprogresssettingsform.h"

class QtMaterialCircularProgress;

class CircularProgressSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit CircularProgressSettingsEditor(QWidget *parent = 0);
    ~CircularProgressSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::CircularProgressSettingsForm *const ui;
    QtMaterialCircularProgress *const m_progress;
};

#endif  // CIRCULARPROGRESSSETTINGSEDITOR_H
