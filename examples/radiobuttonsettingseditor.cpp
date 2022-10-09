#include "radiobuttonsettingseditor.h"

#include <QColorDialog>
#include <QRadioButton>
#include <QVBoxLayout>

#include <qtmaterialradiobutton.h>

RadioButtonSettingsEditor::RadioButtonSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::RadioButtonSettingsForm),
      m_radioButton1(new QtMaterialRadioButton),
      m_radioButton2(new QtMaterialRadioButton),
      m_radioButton3(new QtMaterialRadioButton)
{
    ui->setupUi(_settingsWidget);

    m_radioButton1->setText(tr("Coffee"));
    m_radioButton2->setText(tr("Tea"));
    m_radioButton3->setText(tr("Algebraic Topology"));

    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);
    //_canvas->setMaximumHeight(350);

    QWidget *buttonWidget = new QWidget;
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonWidget->setLayout(buttonLayout);

    layout->addWidget(buttonWidget);
    buttonLayout->addWidget(m_radioButton1);
    buttonLayout->addWidget(m_radioButton2);
    buttonLayout->addWidget(m_radioButton3);

    QSizePolicy policy;
    policy.setHorizontalPolicy(QSizePolicy::Maximum);
    buttonWidget->setSizePolicy(policy);

    layout->setAlignment(Qt::AlignCenter);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    setupForm();

    connect(ui->disabledCheckBox, &QAbstractButton::toggled, this, &RadioButtonSettingsEditor::updateWidget);
    connect(ui->labelPositionComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->labelTextLineEdit, &QLineEdit::textChanged, this, &RadioButtonSettingsEditor::updateWidget);
    connect(ui->useThemeColorsCheckBox, &QAbstractButton::toggled, this, &RadioButtonSettingsEditor::updateWidget);
    connect(ui->textColorToolButton, &QAbstractButton::pressed, this, &RadioButtonSettingsEditor::selectColor);
    connect(ui->disabledColorToolButton, &QAbstractButton::pressed, this, &RadioButtonSettingsEditor::selectColor);
    connect(ui->checkedColorToolButton, &QAbstractButton::pressed, this, &RadioButtonSettingsEditor::selectColor);
    connect(ui->uncheckedColorToolButton, &QAbstractButton::pressed, this, &RadioButtonSettingsEditor::selectColor);
    connect(ui->labelPositionComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
}

RadioButtonSettingsEditor::~RadioButtonSettingsEditor()
{
    delete ui;
}

void RadioButtonSettingsEditor::setupForm()
{
    switch (m_radioButton1->labelPosition())
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

    ui->disabledCheckBox->setChecked(!m_radioButton1->isEnabled());
    ui->labelTextLineEdit->setText(m_radioButton1->text());
    ui->useThemeColorsCheckBox->setChecked(m_radioButton1->useThemeColors());
    setLineEditColor(ui->textColorLineEdit, m_radioButton1->textColor());
    setLineEditColor(ui->disabledColorLineEdit, m_radioButton1->disabledColor());
    setLineEditColor(ui->checkedColorLineEdit, m_radioButton1->checkedColor());
    setLineEditColor(ui->uncheckedColorLineEdit, m_radioButton1->uncheckedColor());
}

void RadioButtonSettingsEditor::updateWidget()
{
    switch (ui->labelPositionComboBox->currentIndex())
    {
        case 0:
            m_radioButton1->setLabelPosition(QtMaterialCheckable::LabelPositionLeft);
            m_radioButton2->setLabelPosition(QtMaterialCheckable::LabelPositionLeft);
            m_radioButton3->setLabelPosition(QtMaterialCheckable::LabelPositionLeft);
            break;

        case 1:
            m_radioButton1->setLabelPosition(QtMaterialCheckable::LabelPositionRight);
            m_radioButton2->setLabelPosition(QtMaterialCheckable::LabelPositionRight);
            m_radioButton3->setLabelPosition(QtMaterialCheckable::LabelPositionRight);
            break;

        default:
            break;
    }

    m_radioButton1->setDisabled(ui->disabledCheckBox->isChecked());
    m_radioButton1->setText(ui->labelTextLineEdit->text());
    m_radioButton1->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    m_radioButton2->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    m_radioButton3->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
}

void RadioButtonSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec() != 0)
    {
        QColor color = dialog.selectedColor();
        if (sender() == ui->textColorToolButton)
        {
            m_radioButton1->setTextColor(color);
            m_radioButton2->setTextColor(color);
            m_radioButton3->setTextColor(color);
        }
        else if (sender() == ui->disabledColorToolButton)
        {
            m_radioButton1->setDisabledColor(color);
            m_radioButton2->setDisabledColor(color);
            m_radioButton3->setDisabledColor(color);
        }
        else if (sender() == ui->checkedColorToolButton)
        {
            m_radioButton1->setCheckedColor(color);
            m_radioButton2->setCheckedColor(color);
            m_radioButton3->setCheckedColor(color);
        }
        else if (sender() == ui->uncheckedColorToolButton)
        {
            m_radioButton1->setUncheckedColor(color);
            m_radioButton2->setUncheckedColor(color);
            m_radioButton3->setUncheckedColor(color);
        }
        ui->useThemeColorsCheckBox->setChecked(false);
    }
    setupForm();
}
