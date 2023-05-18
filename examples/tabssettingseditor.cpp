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
    layout->addWidget(m_tabs, Qt::AlignHCenter);
    _canvas->setLayout(layout);

    m_tabs->addTab(tr("Media"));
    m_tabs->addTab(tr("Audio"));
    m_tabs->addTab(tr("Video"));
    m_tabs->addTab(tr("Tools"));

    m_tabs->setMinimumWidth(500);

    setupForm();

    connect(ui->iconCheckBox, &QAbstractButton::toggled, this, &TabsSettingsEditor::updateWidget);
    connect(ui->haloEnabledCheckBox, &QAbstractButton::toggled, this, &TabsSettingsEditor::updateWidget);
    connect(ui->iconsSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &TabsSettingsEditor::updateWidget);
    connect(ui->useThemeColorsCheckBox, &QAbstractButton::toggled, this, &TabsSettingsEditor::updateWidget);
    connect(ui->inkColorToolButton, &QAbstractButton::clicked, this, &TabsSettingsEditor::selectColor);
    connect(ui->backgroundColorToolButton, &QAbstractButton::clicked, this, &TabsSettingsEditor::selectColor);
    connect(ui->textColorToolButton, &QAbstractButton::clicked, this, &TabsSettingsEditor::selectColor);
}

TabsSettingsEditor::~TabsSettingsEditor()
{
    delete ui;
}

void TabsSettingsEditor::setupForm()
{
    ui->iconsSizeSpinBox->setValue(m_tabs->iconSize().width());
    ui->useThemeColorsCheckBox->setChecked(m_tabs->useThemeColors());
    setLineEditColor(ui->inkColorLineEdit, m_tabs->inkColor());
    setLineEditColor(ui->backgroundColorLineEdit, m_tabs->backgroundColor());
    setLineEditColor(ui->textColorLineEdit, m_tabs->textColor());
}

void TabsSettingsEditor::updateWidget()
{
    m_tabs->setTabIcon(0, ui->iconCheckBox->isChecked() ? QtMaterialTheme::icon("action", "perm_media") : QIcon());
    m_tabs->setTabIcon(1, ui->iconCheckBox->isChecked() ? QtMaterialTheme::icon("image", "audiotrack") : QIcon());
    m_tabs->setTabIcon(2, ui->iconCheckBox->isChecked() ? QtMaterialTheme::icon("notification", "ondemand_video") : QIcon());
    m_tabs->setTabIcon(3, ui->iconCheckBox->isChecked() ? QtMaterialTheme::icon("action", "settings") : QIcon());

    m_tabs->setHaloVisible(ui->haloEnabledCheckBox->isChecked());
    m_tabs->setIconSize(ui->iconsSizeSpinBox->value(), ui->iconsSizeSpinBox->value());
    m_tabs->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
}

void TabsSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec() != 0)
    {
        QColor color = dialog.selectedColor();
        if (sender() == ui->inkColorToolButton)
        {
            m_tabs->setInkColor(color);
        }
        else if (sender() == ui->backgroundColorToolButton)
        {
            m_tabs->setBackgroundColor(color);
        }
        else if (sender() == ui->textColorToolButton)
        {
            m_tabs->setTextColor(color);
        }
        ui->useThemeColorsCheckBox->setChecked(false);
    }
    setupForm();
}
