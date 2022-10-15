#ifndef BADGESETTINGSEDITOR_H
#define BADGESETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_badgesettingsform.h"

class QtMaterialAvatar;
class QtMaterialBadge;

class BadgeSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit BadgeSettingsEditor(QWidget *parent = nullptr);
    ~BadgeSettingsEditor() override;

protected slots:
    void setupForm() override;
    void updateWidget() override;
    void selectColor();

private:
    Ui::BadgeSettingsForm *const ui;
    QtMaterialAvatar *const m_avatar;
    QtMaterialBadge *const m_badge;
};

#endif  // BADGESETTINGSEDITOR_H
