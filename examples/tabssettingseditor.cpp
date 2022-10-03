#include "tabssettingseditor.h"

#include <QColorDialog>
#include <QVBoxLayout>

#include <qtmaterialtabs.h>

TabsSettingsEditor::TabsSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::TabsSettingsForm),
      m_tabs(new QtMaterialTabs)
{
    ui->setupUi(_settingsWidget);

    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);
    layout->addWidget(m_tabs);
    layout->setAlignment(m_tabs, Qt::AlignHCenter);

    m_tabs->addTab("Media");
    m_tabs->addTab("Playback");
    m_tabs->addTab("Audio");
    m_tabs->addTab("Video");
    m_tabs->addTab("Tools");

    m_tabs->setMinimumWidth(700);

    setupForm();
}

TabsSettingsEditor::~TabsSettingsEditor()
{
    delete ui;
}

void TabsSettingsEditor::setupForm()
{
}

void TabsSettingsEditor::updateWidget()
{
}
