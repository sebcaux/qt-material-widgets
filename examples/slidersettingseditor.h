#ifndef SLIDERSETTINGSEDITOR_H
#define SLIDERSETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_slidersettingsform.h"

class QtMaterialSlider;

class SliderSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit SliderSettingsEditor(QWidget *parent = nullptr);
    ~SliderSettingsEditor() override;

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::SliderSettingsForm *const ui;
    QtMaterialSlider *const m_slider;
};

#endif  // SLIDERSETTINGSEDITOR_H
