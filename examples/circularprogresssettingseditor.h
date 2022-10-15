#ifndef CIRCULARPROGRESSSETTINGSEDITOR_H
#define CIRCULARPROGRESSSETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_circularprogresssettingsform.h"

class QtMaterialCircularProgress;

class CircularProgressSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit CircularProgressSettingsEditor(QWidget *parent = nullptr);
    ~CircularProgressSettingsEditor() override;

protected slots:
    void setupForm() override;
    void updateWidget() override;
    void selectColor();

private:
    Ui::CircularProgressSettingsForm *const ui;
    QtMaterialCircularProgress *const m_progress;
};

#endif  // CIRCULARPROGRESSSETTINGSEDITOR_H
