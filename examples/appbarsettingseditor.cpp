#include "appbarsettingseditor.h"
#include <qtmaterialappbar.h>
#include <lib/qtmaterialtheme.h>

AppBarSettingsEditor::AppBarSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::AppBarSettingsForm),
      m_appbar(new QtMaterialAppBar(QChar('X')))
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *widget = new QWidget;
    layout->addWidget(widget);

    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");
    layout->addWidget(canvas);

    ui->setupUi(widget);
    layout->setContentsMargins(20, 20, 20, 20);

    layout = new QVBoxLayout;
    canvas->setLayout(layout);
    layout->addWidget(m_appBar);

    setupForm();
}

AppBarSettingsEditor::~AppBarSettingsEditor()
{
    delete ui;
}

void AppBarSettingsEditor::setupForm()
{
    //switch (m_avatar->type())
    //{
    //case Material::LetterAppBar:
    //    ui->typeComboBox->setCurrentIndex(0);
    //    break;
    //case Material::ImageAppBar:
    //    ui->typeComboBox->setCurrentIndex(1);
    //    break;
    //case Material::IconAppBar:
    //    ui->typeComboBox->setCurrentIndex(2);
    //    break;
    //default:
    //    break;
    //}

    //ui->disabledCheckBox->setChecked(!m_avatar->isEnabled());
    //ui->useThemeColorsCheckBox->setChecked(m_avatar->useThemeColors());
    //ui->sizeSpinBox->setValue(m_avatar->size());
}

void AppBarSettingsEditor::updateWidget()
{
    //switch (ui->typeComboBox->currentIndex())
    //{
    //case 0:
    //    m_avatar->setLetter(QChar('X'));
    //    break;
    //case 1:
    //    m_avatar->setImage(QImage(":/images/assets/sikh.jpg"));
    //    break;
    //case 2:
    //    m_avatar->setIcon(QtMaterialTheme::icon("communication", "message"));
    //    break;
    //default:
    //    break;
    //}

    //m_avatar->setDisabled(ui->disabledCheckBox->isChecked());
    //m_avatar->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    //m_avatar->setSize(ui->sizeSpinBox->value());
}
