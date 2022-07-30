#include "checkboxsettingseditor.h"

#include <QColorDialog>
#include <QVBoxLayout>

#include <qtmaterialcheckbox.h>

CheckBoxSettingsEditor::CheckBoxSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::CheckBoxSettingsForm),
      m_checkBox(new QtMaterialCheckBox)
{
    ui->setupUi(_settingsWidget);

    m_checkBox->setText("Extra cheese");
    m_checkBox->setChecked(true);

    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);
    layout->addWidget(m_checkBox);
    layout->setAlignment(m_checkBox, Qt::AlignCenter);

    setupForm();

    connect(ui->disabledCheckBox, &QAbstractButton::toggled, this, &CheckBoxSettingsEditor::updateWidget);
    connect(ui->labelPositionComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->labelTextLineEdit, &QLineEdit::textChanged, this, &CheckBoxSettingsEditor::updateWidget);
    connect(ui->useThemeColorsCheckBox, &QAbstractButton::toggled, this, &CheckBoxSettingsEditor::updateWidget);
    connect(ui->checkedCheckBox, &QAbstractButton::toggled, this, &CheckBoxSettingsEditor::updateWidget);
    connect(ui->textColorToolButton, &QAbstractButton::pressed, this, &CheckBoxSettingsEditor::selectColor);
    connect(ui->disabledColorToolButton, &QAbstractButton::pressed, this, &CheckBoxSettingsEditor::selectColor);
    connect(ui->checkedColorToolButton, &QAbstractButton::pressed, this, &CheckBoxSettingsEditor::selectColor);
    connect(ui->uncheckedColorToolButton, &QAbstractButton::pressed, this, &CheckBoxSettingsEditor::selectColor);
    connect(m_checkBox, &QAbstractButton::toggled, this, &CheckBoxSettingsEditor::setupForm);
}

CheckBoxSettingsEditor::~CheckBoxSettingsEditor()
{
    delete ui;
}

void CheckBoxSettingsEditor::setupForm()
{
    switch (m_checkBox->labelPosition())
    {
        case QtMaterialCheckable::LabelPositionLeft:
            ui->labelPositionComboBox->setCurrentIndex(0);
            break;
        case QtMaterialCheckable::LabelPositionRight:
            ui->labelPositionComboBox->setCurrentIndex(1);
            break;
        default:
            break;
    }

    ui->disabledCheckBox->setChecked(!m_checkBox->isEnabled());
    ui->labelTextLineEdit->setText(m_checkBox->text());
    ui->useThemeColorsCheckBox->setChecked(m_checkBox->useThemeColors());
    ui->checkedCheckBox->setChecked(m_checkBox->isChecked());
}

void CheckBoxSettingsEditor::updateWidget()
{
    switch (ui->labelPositionComboBox->currentIndex())
    {
        case 0:
            m_checkBox->setLabelPosition(QtMaterialCheckable::LabelPositionLeft);
            break;
        case 1:
            m_checkBox->setLabelPosition(QtMaterialCheckable::LabelPositionRight);
            break;
        default:
            break;
    }

    m_checkBox->setDisabled(ui->disabledCheckBox->isChecked());
    m_checkBox->setText(ui->labelTextLineEdit->text());
    m_checkBox->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    m_checkBox->setChecked(ui->checkedCheckBox->isChecked());
}

void CheckBoxSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec() != 0)
    {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("textColorToolButton" == senderName)
        {
            m_checkBox->setTextColor(color);
            ui->textColorLineEdit->setText(color.name(QColor::HexRgb));
        }
        else if ("disabledColorToolButton" == senderName)
        {
            m_checkBox->setDisabledColor(color);
            ui->disabledColorLineEdit->setText(color.name(QColor::HexRgb));
        }
        else if ("checkedColorToolButton" == senderName)
        {
            m_checkBox->setCheckedColor(color);
            ui->checkedColorLineEdit->setText(color.name(QColor::HexRgb));
        }
        else if ("uncheckedColorToolButton" == senderName)
        {
            m_checkBox->setUncheckedColor(color);
            ui->uncheckedColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
