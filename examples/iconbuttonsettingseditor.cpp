#include "iconbuttonsettingseditor.h"

#include <QColorDialog>

#include <lib/qtmaterialtheme.h>
#include <qtmaterialiconbutton.h>

IconButtonSettingsEditor::IconButtonSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::IconButtonSettingsForm),
      m_button(new QtMaterialIconButton(QtMaterialTheme::icon("toggle", "star")))
{
    init();
}

IconButtonSettingsEditor::~IconButtonSettingsEditor()
{
    delete ui;
}

IconButtonSettingsEditor::IconButtonSettingsEditor(QtMaterialIconButton *button, QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::IconButtonSettingsForm),
      m_button(button)
{
    init();
}

void IconButtonSettingsEditor::setupForm()
{
    ui->disabledCheckBox->setChecked(!m_button->isEnabled());
    ui->useThemeColorsCheckBox->setChecked(m_button->useThemeColors());
    ui->sizeSpinBox->setValue(m_button->iconSize().width());
    ui->colorLineEdit->setText(m_button->color().name(QColor::HexRgb).toUpper());
    setLineEditColor(ui->disabledColorLineEdit, m_button->disabledColor());
}

void IconButtonSettingsEditor::updateWidget()
{
    m_button->setDisabled(ui->disabledCheckBox->isChecked());
    m_button->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    m_button->setIconSize(QSize(ui->sizeSpinBox->value(), ui->sizeSpinBox->value()));
}

void IconButtonSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec() != 0)
    {
        QColor color = dialog.selectedColor();
        if (sender() == ui->colorToolButton)
        {
            m_button->setColor(color);
        }
        else if (sender() == ui->disabledColorToolButton)
        {
            m_button->setDisabledColor(color);
        }
        ui->useThemeColorsCheckBox->setChecked(false);
    }
    setupForm();
}

void IconButtonSettingsEditor::init()
{
    ui->setupUi(_settingsWidget);

    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);
    layout->addWidget(m_button);
    layout->setAlignment(m_button, Qt::AlignCenter);

    setupForm();

    connect(ui->disabledCheckBox, &QAbstractButton::toggled, this, &IconButtonSettingsEditor::updateWidget);
    connect(ui->useThemeColorsCheckBox, &QAbstractButton::toggled, this, &IconButtonSettingsEditor::updateWidget);
    connect(ui->colorToolButton, &QAbstractButton::clicked, this, &IconButtonSettingsEditor::selectColor);
    connect(ui->disabledColorToolButton, &QAbstractButton::clicked, this, &IconButtonSettingsEditor::selectColor);
    connect(ui->sizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
}
