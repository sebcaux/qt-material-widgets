#ifndef AVATARSETTINGSEDITOR_H
#define AVATARSETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_avatarsettingsform.h"

class QtMaterialAvatar;

class AvatarSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit AvatarSettingsEditor(QWidget *parent = nullptr);
    ~AvatarSettingsEditor() override;

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::AvatarSettingsForm *const ui;
    QtMaterialAvatar *const m_avatar;
};

#endif  // AVATARSETTINGSEDITOR_H
