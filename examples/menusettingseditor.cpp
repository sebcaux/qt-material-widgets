#include "menusettingseditor.h"

#include <QVBoxLayout>
#include <QDebug>

#include <qtmaterialmenu.h>

MenuSettingsEditor::MenuSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      m_menu(new QtMaterialMenu)
{
    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);

    layout->addWidget(m_menu);
    layout->addSpacing(600);
    layout->setAlignment(m_menu, Qt::AlignCenter);

    setupForm();
}

MenuSettingsEditor::~MenuSettingsEditor()
{
}

void MenuSettingsEditor::setupForm()
{
}

void MenuSettingsEditor::updateWidget()
{
}

void MenuSettingsEditor::selectColor()
{
}
