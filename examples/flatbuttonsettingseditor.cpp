#include "flatbuttonsettingseditor.h"

#include <QColorDialog>
#include <qtmaterialflatbutton.h>

FlatButtonSettingsEditor::FlatButtonSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::FlatButtonSettingsForm),
      m_button(new QtMaterialFlatButton("I'm flat"))
{
    init();
}

FlatButtonSettingsEditor::~FlatButtonSettingsEditor()
{
    delete ui;
}

FlatButtonSettingsEditor::FlatButtonSettingsEditor(QtMaterialFlatButton *button, QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::FlatButtonSettingsForm),
      m_button(button)
{
    init();
}

void FlatButtonSettingsEditor::setupForm()
{
    switch (m_button->role())
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

    switch (m_button->type())
    {
        case Material::ButtonText:
            ui->buttonTypeComboBox->setCurrentIndex(0);
            break;

        case Material::ButtonOutlined:
            ui->buttonTypeComboBox->setCurrentIndex(1);
            break;

        case Material::ButtonRaised:
            ui->buttonTypeComboBox->setCurrentIndex(2);
            break;

        case Material::ButtonFlat:
            ui->buttonTypeComboBox->setCurrentIndex(3);
            break;

        default:
            break;
    }

    switch (m_button->overlayStyle())
    {
        case Material::NoOverlay:
            ui->hoverStyleComboBox->setCurrentIndex(0);
            break;

        case Material::TintedOverlay:
            ui->hoverStyleComboBox->setCurrentIndex(1);
            break;

        case Material::GrayOverlay:
            ui->hoverStyleComboBox->setCurrentIndex(2);
            break;

        default:
            break;
    }

    switch (m_button->rippleStyle())
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

    switch (m_button->iconPlacement())
    {
        case Material::LeftIcon:
            ui->iconPlacementComboBox->setCurrentIndex(0);
            break;

        case Material::RightIcon:
            ui->iconPlacementComboBox->setCurrentIndex(1);
            break;
    }

    switch (m_button->textAlignment())
    {
        case Qt::AlignLeft:
            ui->textAlignmentComboBox->setCurrentIndex(0);
            break;

        default:
            ui->textAlignmentComboBox->setCurrentIndex(1);
            break;
    }

    ui->checkedCheckBox->setEnabled(m_button->isCheckable());

    ui->disabledCheckBox->setChecked(!m_button->isEnabled());
    ui->checkableCheckBox->setChecked(m_button->isCheckable());
    ui->checkedCheckBox->setChecked(m_button->isChecked());
    ui->showHaloCheckBox->setChecked(m_button->isHaloVisible());
    ui->iconCheckBox->setChecked(!m_button->icon().isNull());
    ui->useThemeColorsCheckBox->setChecked(m_button->useThemeColors());
    ui->cornerRadiusSpinBox->setValue(m_button->cornerRadius());
    ui->overlayOpacityDoubleSpinBox->setValue(m_button->baseOpacity());
    ui->iconSizeSpinBox->setValue(m_button->iconSize().width());
    ui->fontSizeDoubleSpinBox->setValue(m_button->fontSize());
    ui->buttonTextLineEdit->setText(m_button->text());
    setLineEditColor(ui->foregroundColorLineEdit, m_button->foregroundColor());
    setLineEditColor(ui->backgroundColorLineEdit, m_button->backgroundColor());
    setLineEditColor(ui->overlayColorLineEdit, m_button->overlayColor());
    setLineEditColor(ui->disableFgColorLineEdit, m_button->disabledForegroundColor());
    setLineEditColor(ui->disabledBgColorLineEdit, m_button->disabledBackgroundColor());
}

void FlatButtonSettingsEditor::updateWidget()
{
    switch (ui->buttonRoleComboBox->currentIndex())
    {
        case 0:
            m_button->setRole(Material::Default);
            break;

        case 1:
            m_button->setRole(Material::Primary);
            break;

        case 2:
            m_button->setRole(Material::Secondary);
            break;

        default:
            break;
    }

    switch (ui->buttonTypeComboBox->currentIndex())
    {
        case 0:
            m_button->setType(Material::ButtonText);
            break;

        case 1:
            m_button->setType(Material::ButtonOutlined);
            break;

        case 2:
            m_button->setType(Material::ButtonRaised);
            break;

        case 3:
            m_button->setType(Material::ButtonFlat);
            break;

        default:
            break;
    }

    switch (ui->hoverStyleComboBox->currentIndex())
    {
        case 0:
            m_button->setOverlayStyle(Material::NoOverlay);
            break;

        case 1:
            m_button->setOverlayStyle(Material::TintedOverlay);
            break;

        case 2:
            m_button->setOverlayStyle(Material::GrayOverlay);
            break;

        default:
            break;
    }

    switch (ui->rippleStyleComboBox->currentIndex())
    {
        case 0:
            m_button->setRippleStyle(Material::CenteredRipple);
            break;

        case 1:
            m_button->setRippleStyle(Material::PositionedRipple);
            break;

        case 2:
            m_button->setRippleStyle(Material::NoRipple);
            break;

        default:
            break;
    }

    switch (ui->iconPlacementComboBox->currentIndex())
    {
        case 0:
            m_button->setIconPlacement(Material::LeftIcon);
            break;

        case 1:
            m_button->setIconPlacement(Material::RightIcon);
            break;

        default:
            break;
    }

    switch (ui->textAlignmentComboBox->currentIndex())
    {
        case 0:
            m_button->setTextAlignment(Qt::AlignLeft);
            break;

        case 1:
        default:
            m_button->setTextAlignment(Qt::AlignHCenter);
            break;
    }

    m_button->setDisabled(ui->disabledCheckBox->isChecked());
    m_button->setCheckable(ui->checkableCheckBox->isChecked());
    m_button->setChecked(ui->checkedCheckBox->isChecked());
    m_button->setHaloVisible(ui->showHaloCheckBox->isChecked());
    m_button->setIcon(ui->iconCheckBox->isChecked() ? QtMaterialTheme::icon("toggle", "star") : QIcon());
    m_button->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    m_button->setCornerRadius(ui->cornerRadiusSpinBox->value());
    m_button->setBaseOpacity(ui->overlayOpacityDoubleSpinBox->value());
    m_button->setIconSize(QSize(ui->iconSizeSpinBox->value(), ui->iconSizeSpinBox->value()));
    m_button->setFontSize(ui->fontSizeDoubleSpinBox->value());
    m_button->setText(ui->buttonTextLineEdit->text());

    ui->checkedCheckBox->setEnabled(m_button->isCheckable());
}

void FlatButtonSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec() != 0)
    {
        QColor color = dialog.selectedColor();
        if (sender() == ui->foregroundColorToolButton)
        {
            m_button->setForegroundColor(color);
        }
        else if (sender() == ui->backgroundColorToolButton)
        {
            m_button->setBackgroundColor(color);
        }
        else if (sender() == ui->overlayColorToolButton)
        {
            m_button->setOverlayColor(color);
        }
        else if (sender() == ui->disabledFgColorToolButton)
        {
            m_button->setDisabledForegroundColor(color);
        }
        else if (sender() == ui->disabledBgColorToolButton)
        {
            m_button->setDisabledBackgroundColor(color);
        }
        ui->useThemeColorsCheckBox->setChecked(false);
    }
    setupForm();
}

void FlatButtonSettingsEditor::init()
{
    ui->setupUi(_settingsWidget);

    m_button->setFixedWidth(300);

    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);
    layout->addWidget(m_button);
    layout->setAlignment(m_button, Qt::AlignCenter);

    setupForm();

    connect(ui->disabledCheckBox, &QAbstractButton::toggled, this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->checkableCheckBox, &QAbstractButton::toggled, this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->checkedCheckBox, &QAbstractButton::toggled, this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->showHaloCheckBox, &QAbstractButton::toggled, this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->iconCheckBox, &QAbstractButton::toggled, this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->buttonRoleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->buttonTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->rippleStyleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->hoverStyleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->iconPlacementComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->textAlignmentComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->cornerRadiusSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->overlayOpacityDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->iconSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->fontSizeDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->buttonTextLineEdit, &QLineEdit::textChanged, this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->useThemeColorsCheckBox, &QAbstractButton::toggled, this, &FlatButtonSettingsEditor::updateWidget);
    connect(ui->foregroundColorToolButton, &QAbstractButton::clicked, this, &FlatButtonSettingsEditor::selectColor);
    connect(ui->backgroundColorToolButton, &QAbstractButton::clicked, this, &FlatButtonSettingsEditor::selectColor);
    connect(ui->disabledFgColorToolButton, &QAbstractButton::clicked, this, &FlatButtonSettingsEditor::selectColor);
    connect(ui->disabledBgColorToolButton, &QAbstractButton::clicked, this, &FlatButtonSettingsEditor::selectColor);
    connect(ui->overlayColorToolButton, &QAbstractButton::clicked, this, &FlatButtonSettingsEditor::selectColor);
    connect(m_button, &QAbstractButton::clicked, ui->checkedCheckBox, &QAbstractButton::setChecked);
}
