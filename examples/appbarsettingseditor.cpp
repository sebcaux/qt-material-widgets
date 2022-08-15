#include "appbarsettingseditor.h"

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

    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);
    layout->addWidget(m_appBar);
    layout->addStretch(1);

    setupForm();

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
    ui->useThemeColorsCheckBox->setChecked(m_appBar->useThemeColors());
}

void AppBarSettingsEditor::updateWidget()
{
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
