#ifndef ICONMENUSETTINGSEDITOR_H
#define ICONMENUSETTINGSEDITOR_H

#include <QWidget>
#include "ui_iconmenusettingsform.h"

class QtMaterialIconMenu;

class IconMenuSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit IconMenuSettingsEditor(QWidget *parent = 0);
    ~IconMenuSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::IconMenuSettingsForm *const ui;
    QtMaterialIconMenu       *const m_iconMenu;
};

#endif // ICONMENUSETTINGSEDITOR_H
