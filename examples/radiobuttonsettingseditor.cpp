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

    m_radioButton1->setText("Coffee");
    m_radioButton2->setText("Tea");
    m_radioButton3->setText("Algebraic Topology");

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
    connect(ui->labelPositionComboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->labelTextLineEdit_2, &QLineEdit::textChanged, this, &RadioButtonSettingsEditor::updateWidget);
    connect(ui->useThemeColorsCheckBox_3, &QAbstractButton::toggled, this, &RadioButtonSettingsEditor::updateWidget);
    connect(ui->textColorToolButton_2, &QAbstractButton::pressed, this, &RadioButtonSettingsEditor::selectColor);
    connect(ui->disabledColorToolButton_2, &QAbstractButton::pressed, this, &RadioButtonSettingsEditor::selectColor);
    connect(ui->checkedColorToolButton_2, &QAbstractButton::pressed, this, &RadioButtonSettingsEditor::selectColor);
    connect(ui->uncheckedColorToolButton_2, &QAbstractButton::pressed, this, &RadioButtonSettingsEditor::selectColor);
    connect(ui->labelPositionComboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
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
            ui->labelPositionComboBox_2->setCurrentIndex(0);
            break;
        case QtMaterialCheckable::LabelPositionRight:
            ui->labelPositionComboBox_2->setCurrentIndex(1);
            break;
        default:
            break;
    }

    ui->disabledCheckBox->setChecked(!m_radioButton1->isEnabled());
    ui->labelTextLineEdit_2->setText(m_radioButton1->text());
    ui->useThemeColorsCheckBox_3->setChecked(m_radioButton1->useThemeColors());
}

void RadioButtonSettingsEditor::updateWidget()
{
    switch (ui->labelPositionComboBox_2->currentIndex())
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
    m_radioButton1->setText(ui->labelTextLineEdit_2->text());
    m_radioButton1->setUseThemeColors(ui->useThemeColorsCheckBox_3->isChecked());
    m_radioButton2->setUseThemeColors(ui->useThemeColorsCheckBox_3->isChecked());
    m_radioButton3->setUseThemeColors(ui->useThemeColorsCheckBox_3->isChecked());
}

void RadioButtonSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec() != 0)
    {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("textColorToolButton_2" == senderName)
        {
            m_radioButton1->setTextColor(color);
            m_radioButton2->setTextColor(color);
            m_radioButton3->setTextColor(color);
            ui->textColorLineEdit_2->setText(color.name(QColor::HexRgb));
        }
        else if ("disabledColorToolButton_2" == senderName)
        {
            m_radioButton1->setDisabledColor(color);
            m_radioButton2->setDisabledColor(color);
            m_radioButton3->setDisabledColor(color);
            ui->disabledColorLineEdit_2->setText(color.name(QColor::HexRgb));
        }
        else if ("checkedColorToolButton_2" == senderName)
        {
            m_radioButton1->setCheckedColor(color);
            m_radioButton2->setCheckedColor(color);
            m_radioButton3->setCheckedColor(color);
            ui->checkedColorLineEdit_2->setText(color.name(QColor::HexRgb));
        }
        else if ("uncheckedColorToolButton_2" == senderName)
        {
            m_radioButton1->setUncheckedColor(color);
            m_radioButton2->setUncheckedColor(color);
            m_radioButton3->setUncheckedColor(color);
            ui->uncheckedColorLineEdit_2->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
