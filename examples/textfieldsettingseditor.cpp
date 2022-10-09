#include "textfieldsettingseditor.h"

#include <QColorDialog>
#include <QVBoxLayout>

#include <qtmaterialtextfield.h>

TextFieldSettingsEditor::TextFieldSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::TextFieldSettingsForm),
      m_textField(new QtMaterialTextField)
{
    ui->setupUi(_settingsWidget);

    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);

    layout->addWidget(m_textField);
    layout->setAlignment(m_textField, Qt::AlignCenter);

    m_textField->setLabelText("Wat is this");
    m_textField->setMinimumWidth(250);

    setupForm();

    connect(ui->disabledCheckBox, &QAbstractButton::toggled, this, &TextFieldSettingsEditor::updateWidget);
    connect(ui->textLineEdit, &QLineEdit::textChanged, this, &TextFieldSettingsEditor::updateWidget);
    connect(ui->placeholderLineEdit, &QLineEdit::textChanged, this, &TextFieldSettingsEditor::updateWidget);
    connect(ui->labelCheckBox, &QAbstractButton::toggled, this, &TextFieldSettingsEditor::updateWidget);
    connect(ui->labelTextLineEdit, &QLineEdit::textChanged, this, &TextFieldSettingsEditor::updateWidget);
    connect(ui->useThemeColorsCheckBox, &QAbstractButton::toggled, this, &TextFieldSettingsEditor::updateWidget);
    connect(ui->textColorToolButton, &QAbstractButton::pressed, this, &TextFieldSettingsEditor::selectColor);
    connect(ui->inkColorToolButton, &QAbstractButton::pressed, this, &TextFieldSettingsEditor::selectColor);
    connect(ui->inputLineColorToolButton, &QAbstractButton::pressed, this, &TextFieldSettingsEditor::selectColor);
    connect(ui->labelColorToolButton, &QAbstractButton::pressed, this, &TextFieldSettingsEditor::selectColor);
    connect(ui->inputLineCheckBox, &QAbstractButton::toggled, this, &TextFieldSettingsEditor::setShowInputLine);

    connect(m_textField, &QLineEdit::textChanged, this, &TextFieldSettingsEditor::setupForm);
}

TextFieldSettingsEditor::~TextFieldSettingsEditor()
{
    delete ui;
}

void TextFieldSettingsEditor::setupForm()
{
    ui->disabledCheckBox->setChecked(!m_textField->isEnabled());
    ui->textLineEdit->setText(m_textField->text());
    ui->placeholderLineEdit->setText(m_textField->placeholderText());
    ui->labelCheckBox->setChecked(m_textField->labelVisible());
    ui->labelTextLineEdit->setText(m_textField->labelText());
    ui->useThemeColorsCheckBox->setChecked(m_textField->useThemeColors());
    ui->inputLineCheckBox->setChecked(m_textField->inputLineVisible());
    setLineEditColor(ui->textColorLineEdit, m_textField->textColor());
    setLineEditColor(ui->inkColorLineEdit, m_textField->inkColor());
    setLineEditColor(ui->inputLineColorLineEdit, m_textField->inputLineColor());
    setLineEditColor(ui->labelColorLineEdit, m_textField->labelColor());
}

void TextFieldSettingsEditor::updateWidget()
{
    m_textField->setDisabled(ui->disabledCheckBox->isChecked());
    m_textField->setText(ui->textLineEdit->text());
    m_textField->setPlaceholderText(ui->placeholderLineEdit->text());
    m_textField->setLabelText(ui->labelTextLineEdit->text());
    m_textField->setLabelVisible(ui->labelCheckBox->isChecked());
    m_textField->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    m_textField->setInputLineVisible(ui->inputLineCheckBox->isChecked());
}

void TextFieldSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec() != 0)
    {
        QColor color = dialog.selectedColor();
        if (sender() == ui->textColorToolButton)
        {
            m_textField->setTextColor(color);
        }
        else if (sender() == ui->inkColorToolButton)
        {
            m_textField->setInkColor(color);
        }
        else if (sender() == ui->inputLineColorToolButton)
        {
            m_textField->setInputLineColor(color);
        }
        else if (sender() == ui->labelColorToolButton)
        {
            m_textField->setLabelColor(color);
        }
        ui->useThemeColorsCheckBox->setChecked(false);
    }
    setupForm();
}

void TextFieldSettingsEditor::setShowInputLine()
{
    m_textField->setInputLineVisible(ui->inputLineCheckBox->isChecked());
}
