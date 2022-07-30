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

    m_textField->setLabel("Wat is this");
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
    ui->labelCheckBox->setChecked(m_textField->hasLabel());
    ui->labelTextLineEdit->setText(m_textField->label());
    ui->useThemeColorsCheckBox->setChecked(m_textField->useThemeColors());
    ui->inputLineCheckBox->setChecked(m_textField->hasInputLine());
}

void TextFieldSettingsEditor::updateWidget()
{
    m_textField->setDisabled(ui->disabledCheckBox->isChecked());
    m_textField->setText(ui->textLineEdit->text());
    m_textField->setPlaceholderText(ui->placeholderLineEdit->text());
    m_textField->setLabel(ui->labelTextLineEdit->text());
    m_textField->setShowLabel(ui->labelCheckBox->isChecked());
    m_textField->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    m_textField->setShowInputLine(ui->inputLineCheckBox->isChecked());
}

void TextFieldSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec() != 0)
    {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("textColorToolButton" == senderName)
        {
            m_textField->setTextColor(color);
            ui->textColorLineEdit->setText(color.name(QColor::HexRgb));
        }
        else if ("inkColorToolButton" == senderName)
        {
            m_textField->setInkColor(color);
            ui->inkColorLineEdit->setText(color.name(QColor::HexRgb));
        }
        else if ("inputLineColorToolButton" == senderName)
        {
            m_textField->setInputLineColor(color);
            ui->inputLineColorLineEdit->setText(color.name(QColor::HexRgb));
        }
        else if ("labelColorToolButton" == senderName)
        {
            m_textField->setLabelColor(color);
            ui->labelColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}

void TextFieldSettingsEditor::setShowInputLine()
{
    m_textField->setShowInputLine(ui->inputLineCheckBox->isChecked());
}
