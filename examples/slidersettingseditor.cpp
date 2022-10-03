#include "slidersettingseditor.h"

#include <QColorDialog>
#include <QVBoxLayout>

#include <qtmaterialslider.h>

SliderSettingsEditor::SliderSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::SliderSettingsForm),
      m_slider(new QtMaterialSlider)
{
    ui->setupUi(_settingsWidget);

    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);
    // canvas->setMaximumHeight(300);
    layout->addWidget(m_slider);
    layout->setAlignment(m_slider, Qt::AlignHCenter);

    setupForm();

    connect(ui->disabledCheckBox, &QAbstractButton::toggled, this, &SliderSettingsEditor::updateWidget);
    connect(ui->valueLineEdit, &QLineEdit::textChanged, this, &SliderSettingsEditor::updateWidget);
    connect(ui->orientationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->invertedCheckBox, &QAbstractButton::toggled, this, &SliderSettingsEditor::updateWidget);

    connect(m_slider, &QAbstractSlider::valueChanged, this, &SliderSettingsEditor::setupForm);
}

SliderSettingsEditor::~SliderSettingsEditor()
{
    delete ui;
}

void SliderSettingsEditor::setupForm()
{
    switch (m_slider->orientation())
    {
        case Qt::Horizontal:
            ui->orientationComboBox->setCurrentIndex(0);
            break;

        case Qt::Vertical:
            ui->orientationComboBox->setCurrentIndex(1);
            break;

        default:
            break;
    }

    ui->disabledCheckBox->setChecked(!m_slider->isEnabled());
    ui->valueLineEdit->setText(QString::number(m_slider->value()));
    ui->invertedCheckBox->setChecked(m_slider->invertedAppearance());
}

void SliderSettingsEditor::updateWidget()
{
    switch (ui->orientationComboBox->currentIndex())
    {
        case 0:
            m_slider->setOrientation(Qt::Horizontal);
            break;

        case 1:
            m_slider->setOrientation(Qt::Vertical);
            break;

        default:
            break;
    }

    m_slider->setDisabled(ui->disabledCheckBox->isChecked());
    m_slider->setValue(ui->valueLineEdit->text().toInt());
    m_slider->setInvertedAppearance(ui->invertedCheckBox->isChecked());
}
