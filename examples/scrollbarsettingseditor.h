#ifndef SCROLLBARSETTINGSEDITOR_H
#define SCROLLBARSETTINGSEDITOR_H

#include "settingseditor.h"

#include "ui_scrollbarsettingsform.h"

class QtMaterialScrollBar;

class ScrollBarSettingsEditor : public SettingsEditor
{
    Q_OBJECT

public:
    explicit ScrollBarSettingsEditor(QWidget *parent = nullptr);
    ~ScrollBarSettingsEditor() override;

protected slots:
    void setupForm();
    void updateWidget();

private:
    Ui::ScrollBarSettingsForm *const ui;
    QtMaterialScrollBar *const m_verticalScrollbar;
    QtMaterialScrollBar *const m_horizontalScrollbar;
};

#endif  // SCROLLBARSETTINGSEDITOR_H
