#include "badgesettingseditor.h"

#include <QColorDialog>

#include <qtmaterialavatar.h>
#include <qtmaterialbadge.h>

BadgeSettingsEditor::BadgeSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::BadgeSettingsForm),
      m_avatar(new QtMaterialAvatar(QImage(":/images/assets/sikh.jpg"))),
      m_badge(new QtMaterialBadge)
{
    ui->setupUi(_settingsWidget);

    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);
    layout->addWidget(m_avatar);
    layout->setAlignment(m_avatar, Qt::AlignCenter);
    m_avatar->setSize(60);

    m_badge->setParent(m_avatar);
    m_badge->setRelativePosition(18, 18);
    m_badge->setText("3");

    setupForm();

    connect(ui->disabledCheckBox, &QAbstractButton::toggled, this, &BadgeSettingsEditor::updateWidget);
    connect(ui->typeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, &QAbstractButton::toggled, this, &BadgeSettingsEditor::updateWidget);
    connect(ui->horizontalOffsetSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->verticalOffsetSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->backgroundColorToolButton, &QAbstractButton::pressed, this, &BadgeSettingsEditor::selectColor);
    connect(ui->textColorToolButton, &QAbstractButton::pressed, this, &BadgeSettingsEditor::selectColor);

    ui->verticalOffsetSpinBox->setRange(-40, 40);
    ui->horizontalOffsetSpinBox->setRange(-40, 40);
}

BadgeSettingsEditor::~BadgeSettingsEditor()
{
    delete ui;
}

void BadgeSettingsEditor::setupForm()
{
    if (m_badge->icon().isNull())
    {
        ui->typeComboBox->setCurrentIndex(0);
    }
    else
    {
        ui->typeComboBox->setCurrentIndex(1);
    }

    ui->verticalOffsetSpinBox->setValue(m_badge->relativePosition().y());
    ui->horizontalOffsetSpinBox->setValue(m_badge->relativePosition().x());
    ui->disabledCheckBox->setChecked(!m_badge->isEnabled());
    ui->useThemeColorsCheckBox->setChecked(m_badge->useThemeColors());
    setLineEditColor(ui->textColorLineEdit, m_badge->textColor());
    setLineEditColor(ui->backgroundColorLineEdit, m_badge->backgroundColor());
}

void BadgeSettingsEditor::updateWidget()
{
    switch (ui->typeComboBox->currentIndex())
    {
        case 0:
            m_badge->setText("3");
            break;

        case 1:
            m_badge->setIcon(QIcon(QtMaterialTheme::icon("communication", "message")));
            break;

        default:
            break;
    }

    m_badge->setRelativePosition(ui->horizontalOffsetSpinBox->value(), ui->verticalOffsetSpinBox->value());
    m_badge->setDisabled(ui->disabledCheckBox->isChecked());
    m_badge->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
}

void BadgeSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec() != 0)
    {
        QColor color = dialog.selectedColor();
        if (sender() == ui->textColorToolButton)
        {
            m_badge->setTextColor(color);
        }
        else if (sender() == ui->backgroundColorToolButton)
        {
            m_badge->setBackgroundColor(color);
        }
        ui->useThemeColorsCheckBox->setChecked(false);
    }
    setupForm();
}
