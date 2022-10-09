#include "avatarsettingseditor.h"

#include <QColorDialog>

#include <lib/qtmaterialtheme.h>
#include <qtmaterialavatar.h>

AvatarSettingsEditor::AvatarSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::AvatarSettingsForm),
      m_avatar(new QtMaterialAvatar(QChar('X')))
{
    ui->setupUi(_settingsWidget);

    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);
    layout->addWidget(m_avatar);
    layout->setAlignment(m_avatar, Qt::AlignCenter);

    setupForm();

    connect(ui->disabledCheckBox, &QAbstractButton::toggled, this, &AvatarSettingsEditor::updateWidget);
    connect(ui->useThemeColorsCheckBox, &QAbstractButton::toggled, this, &AvatarSettingsEditor::updateWidget);
    connect(ui->sizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->typeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->backgroundColorToolButton, &QAbstractButton::pressed, this, &AvatarSettingsEditor::selectColor);
    connect(ui->textColorToolButton, &QAbstractButton::pressed, this, &AvatarSettingsEditor::selectColor);

    ui->sizeSpinBox->setRange(5, 300);
}

AvatarSettingsEditor::~AvatarSettingsEditor()
{
    delete ui;
}

void AvatarSettingsEditor::setupForm()
{
    switch (m_avatar->type())
    {
        case Material::LetterAvatar:
            ui->typeComboBox->setCurrentIndex(0);
            break;

        case Material::ImageAvatar:
            ui->typeComboBox->setCurrentIndex(1);
            break;

        case Material::IconAvatar:
            ui->typeComboBox->setCurrentIndex(2);
            break;
        default:
            break;
    }

    ui->disabledCheckBox->setChecked(!m_avatar->isEnabled());
    ui->useThemeColorsCheckBox->setChecked(m_avatar->useThemeColors());
    ui->sizeSpinBox->setValue(m_avatar->size());
    setLineEditColor(ui->textColorLineEdit, m_avatar->textColor());
    setLineEditColor(ui->backgroundColorLineEdit, m_avatar->backgroundColor());
}

void AvatarSettingsEditor::updateWidget()
{
    switch (ui->typeComboBox->currentIndex())
    {
        case 0:
            m_avatar->setLetter(QChar('X'));
            break;

        case 1:
            m_avatar->setImage(QImage(":/images/assets/sikh.jpg"));
            break;

        case 2:
            m_avatar->setIcon(QtMaterialTheme::icon("communication", "message"));
            break;

        default:
            break;
    }

    m_avatar->setDisabled(ui->disabledCheckBox->isChecked());
    m_avatar->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    m_avatar->setSize(ui->sizeSpinBox->value());
}

void AvatarSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec() != 0)
    {
        QColor color = dialog.selectedColor();
        if (sender() == ui->textColorToolButton)
        {
            m_avatar->setTextColor(color);
        }
        else if (sender() == ui->backgroundColorToolButton)
        {
            m_avatar->setBackgroundColor(color);
        }
        ui->useThemeColorsCheckBox->setChecked(false);
    }
    setupForm();
}
