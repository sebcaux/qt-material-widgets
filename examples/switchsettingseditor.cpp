#include "switchsettingseditor.h"

#include <QColorDialog>

#include <qtmaterialswitch.h>

SwitchSettingsEditor::SwitchSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::SwitchSettingsForm),
      m_switch(new QtMaterialSwitch)
{
    ui->setupUi(_settingsWidget);

    m_switch->setOrientation(Qt::Vertical);

    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);
    layout->addWidget(m_switch);
    layout->setAlignment(m_switch, Qt::AlignCenter);

    setupForm();

    connect(ui->disabledCheckBox, &QAbstractButton::toggled, this, &SwitchSettingsEditor::updateWidget);
    connect(ui->checkedCheckBox, &QAbstractButton::toggled, this, &SwitchSettingsEditor::updateWidget);
    connect(ui->orientationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, &QAbstractButton::toggled, this, &SwitchSettingsEditor::updateWidget);
    connect(ui->disabledColorToolButton, &QAbstractButton::pressed, this, &SwitchSettingsEditor::selectColor);
    connect(ui->activeColorToolButton, &QAbstractButton::pressed, this, &SwitchSettingsEditor::selectColor);
    connect(ui->inactiveColorToolButton, &QAbstractButton::pressed, this, &SwitchSettingsEditor::selectColor);
    connect(ui->trackColorToolButton, &QAbstractButton::pressed, this, &SwitchSettingsEditor::selectColor);

    connect(m_switch, &QAbstractButton::toggled, this, &SwitchSettingsEditor::setupForm);
}

SwitchSettingsEditor::~SwitchSettingsEditor()
{
}

void SwitchSettingsEditor::setupForm()
{
    switch (m_switch->orientation())
    {
        case Qt::Horizontal:
            ui->orientationComboBox->setCurrentIndex(0);
            break;
        case Qt::Vertical:
            ui->orientationComboBox->setCurrentIndex(1);
            break;
        default:
            break;
    }

    ui->disabledCheckBox->setChecked(!m_switch->isEnabled());
    ui->checkedCheckBox->setChecked(m_switch->isChecked());
    ui->useThemeColorsCheckBox->setChecked(m_switch->useThemeColors());
}

void SwitchSettingsEditor::updateWidget()
{
    switch (ui->orientationComboBox->currentIndex())
    {
        case 0:
            m_switch->setOrientation(Qt::Horizontal);
            break;
        case 1:
            m_switch->setOrientation(Qt::Vertical);
            break;
        default:
            break;
    }

    m_switch->setDisabled(ui->disabledCheckBox->isChecked());
    m_switch->setChecked(ui->checkedCheckBox->isChecked());
    m_switch->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
}

void SwitchSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec() != 0)
    {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("disabledColorToolButton" == senderName)
        {
            m_switch->setDisabledColor(color);
            ui->disabledColorLineEdit->setText(color.name(QColor::HexRgb));
        }
        else if ("activeColorToolButton" == senderName)
        {
            m_switch->setActiveColor(color);
            ui->activeColorLineEdit->setText(color.name(QColor::HexRgb));
        }
        else if ("inactiveColorToolButton" == senderName)
        {
            m_switch->setInactiveColor(color);
            ui->inactiveColorLineEdit->setText(color.name(QColor::HexRgb));
        }
        else if ("trackColorToolButton" == senderName)
        {
            m_switch->setTrackColor(color);
            ui->trackColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
