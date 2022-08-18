#include "fabsettingseditor.h"

#include <QColorDialog>
#include <QDebug>
#include <QVBoxLayout>

#include <qtmaterialfab.h>

FloatingActionButtonSettingsEditor::FloatingActionButtonSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::FloatingActionButtonSettingsForm),
      m_fab(new QtMaterialFloatingActionButton(QtMaterialTheme::icon("toggle", "star")))
{
    ui->setupUi(_settingsWidget);

    m_fab->setParent(_canvas);

    setupForm();

    connect(ui->disabledCheckBox, &QAbstractButton::toggled, this, &FloatingActionButtonSettingsEditor::updateWidget);
    connect(ui->buttonRoleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->cornerComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->horizontalOffsetSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->verticalOffsetSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->miniCheckBox, &QAbstractButton::toggled, this, &FloatingActionButtonSettingsEditor::updateWidget);
    connect(ui->rippleStyleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, &QAbstractButton::toggled, this, &FloatingActionButtonSettingsEditor::updateWidget);
    connect(ui->foregroundColorToolButton, &QAbstractButton::clicked, this, &FloatingActionButtonSettingsEditor::selectColor);
    connect(ui->backgroundColorToolButton, &QAbstractButton::clicked, this, &FloatingActionButtonSettingsEditor::selectColor);
    connect(ui->disabledFgColorToolButton, &QAbstractButton::clicked, this, &FloatingActionButtonSettingsEditor::selectColor);
    connect(ui->disabledBgColorToolButton, &QAbstractButton::clicked, this, &FloatingActionButtonSettingsEditor::selectColor);
}

FloatingActionButtonSettingsEditor::~FloatingActionButtonSettingsEditor()
{
    delete ui;
}

void FloatingActionButtonSettingsEditor::setupForm()
{
    switch (m_fab->role())
    {
        case Material::Default:
            ui->buttonRoleComboBox->setCurrentIndex(0);
            break;
        case Material::Primary:
            ui->buttonRoleComboBox->setCurrentIndex(1);
            break;
        case Material::Secondary:
            ui->buttonRoleComboBox->setCurrentIndex(2);
            break;
        default:
            break;
    }

    switch (m_fab->corner())
    {
        case Qt::TopLeftCorner:
            ui->cornerComboBox->setCurrentIndex(0);
            break;
        case Qt::TopRightCorner:
            ui->cornerComboBox->setCurrentIndex(1);
            break;
        case Qt::BottomLeftCorner:
            ui->cornerComboBox->setCurrentIndex(2);
            break;
        case Qt::BottomRightCorner:
            ui->cornerComboBox->setCurrentIndex(3);
            break;
        default:
            break;
    }

    switch (m_fab->rippleStyle())
    {
        case Material::CenteredRipple:
            ui->rippleStyleComboBox->setCurrentIndex(0);
            break;
        case Material::PositionedRipple:
            ui->rippleStyleComboBox->setCurrentIndex(1);
            break;
        case Material::NoRipple:
            ui->rippleStyleComboBox->setCurrentIndex(2);
            break;
        default:
            break;
    }

    ui->disabledCheckBox->setChecked(!m_fab->isEnabled());
    ui->horizontalOffsetSpinBox->setValue(m_fab->offset().x());
    ui->verticalOffsetSpinBox->setValue(m_fab->offset().y());
    ui->miniCheckBox->setChecked(m_fab->isMini());
    ui->useThemeColorsCheckBox->setChecked(m_fab->useThemeColors());
}

void FloatingActionButtonSettingsEditor::updateWidget()
{
    switch (ui->buttonRoleComboBox->currentIndex())
    {
        case 0:
            m_fab->setRole(Material::Default);
            break;
        case 1:
            m_fab->setRole(Material::Primary);
            break;
        case 2:
            m_fab->setRole(Material::Secondary);
            break;
        default:
            break;
    }

    switch (ui->cornerComboBox->currentIndex())
    {
        case 0:
            m_fab->setCorner(Qt::TopLeftCorner);
            break;
        case 1:
            m_fab->setCorner(Qt::TopRightCorner);
            break;
        case 2:
            m_fab->setCorner(Qt::BottomLeftCorner);
            break;
        case 3:
            m_fab->setCorner(Qt::BottomRightCorner);
            break;
        default:
            break;
    }

    switch (ui->rippleStyleComboBox->currentIndex())
    {
        case 0:
            m_fab->setRippleStyle(Material::CenteredRipple);
            break;
        case 1:
            m_fab->setRippleStyle(Material::PositionedRipple);
            break;
        case 2:
            m_fab->setRippleStyle(Material::NoRipple);
            break;
        default:
            break;
    }

    m_fab->setDisabled(ui->disabledCheckBox->isChecked());
    m_fab->setOffset(ui->horizontalOffsetSpinBox->value(), ui->verticalOffsetSpinBox->value());
    m_fab->setMini(ui->miniCheckBox->isChecked());
    m_fab->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
}

void FloatingActionButtonSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec() != 0)
    {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("foregroundColorToolButton" == senderName)
        {
            m_fab->setForegroundColor(color);
            ui->foregroundColorLineEdit->setText(color.name(QColor::HexRgb));
        }
        else if ("backgroundColorToolButton" == senderName)
        {
            m_fab->setBackgroundColor(color);
            ui->backgroundColorLineEdit->setText(color.name(QColor::HexRgb));
        }
        else if ("disabledFgColorToolButton" == senderName)
        {
            m_fab->setDisabledForegroundColor(color);
            ui->disabledFgColorLineEdit->setText(color.name(QColor::HexRgb));
        }
        else if ("disabledBgColorToolButton" == senderName)
        {
            m_fab->setDisabledBackgroundColor(color);
            ui->disabledBgColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
