#include "appbarsettingseditor.h"

#include <QAction>
#include <QColorDialog>
#include <QVBoxLayout>

#include <lib/qtmaterialtheme.h>
#include <qtmaterialappbar.h>
#include <qtmaterialiconbutton.h>

AppBarSettingsEditor::AppBarSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::AppBarSettingsForm),
      m_appBar(new QtMaterialAppBar)
{
    ui->setupUi(_settingsWidget);

    m_appBar->setTitle("Inbox");
    m_appBar->setNavIconType(Material::NavIconMenu);
    m_appBar->addAction(new QAction(QtMaterialTheme::icon("social", "share"), tr("share")));
    m_appBar->addAction(new QAction(QtMaterialTheme::icon("action", "search"), tr("search")));

    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);
    layout->addWidget(m_appBar);
    layout->addStretch(1);

    setupForm();

    connect(ui->titleLineEdit, &QLineEdit::textEdited, this, &AppBarSettingsEditor::updateWidget);
    connect(ui->navIconTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AppBarSettingsEditor::updateWidget);
    connect(ui->iconsSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &AppBarSettingsEditor::updateWidget);
    connect(ui->useThemeColorsCheckBox, &QAbstractButton::toggled, this, &AppBarSettingsEditor::updateWidget);
    connect(ui->backgroundColorToolButton, &QAbstractButton::pressed, this, &AppBarSettingsEditor::selectColor);
    connect(ui->foregroundColorToolButton, &QAbstractButton::pressed, this, &AppBarSettingsEditor::selectColor);
}

AppBarSettingsEditor::~AppBarSettingsEditor()
{
    delete ui;
}

void AppBarSettingsEditor::setupForm()
{
    ui->navIconTypeComboBox->addItem("NavIconNone", QVariant(Material::NavIconNone));
    ui->navIconTypeComboBox->addItem("NavIconMenu", QVariant(Material::NavIconMenu));
    ui->navIconTypeComboBox->addItem("NavIconPrevious", QVariant(Material::NavIconPrevious));
    ui->navIconTypeComboBox->addItem("NavIconUpper", QVariant(Material::NavIconUpper));

    ui->titleLineEdit->setText(m_appBar->title());
    ui->navIconTypeComboBox->setCurrentIndex(m_appBar->navIconType());
    ui->iconsSizeSpinBox->setValue(m_appBar->iconSize().width());
    ui->useThemeColorsCheckBox->setChecked(m_appBar->useThemeColors());
}

void AppBarSettingsEditor::updateWidget()
{
    m_appBar->setTitle(ui->titleLineEdit->text());
    m_appBar->setNavIconType(static_cast<Material::NavIconType>(ui->navIconTypeComboBox->currentData().toInt()));
    m_appBar->setIconSize(ui->iconsSizeSpinBox->value(), ui->iconsSizeSpinBox->value());
    m_appBar->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
}

void AppBarSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec() != 0)
    {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("backgroundColorToolButton" == senderName)
        {
            m_appBar->setBackgroundColor(color);
            ui->backgroundColorLineEdit->setText(color.name(QColor::HexRgb));
        }
        if ("foregroundColorToolButton" == senderName)
        {
            m_appBar->setForegroundColor(color);
            ui->foregroundColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
