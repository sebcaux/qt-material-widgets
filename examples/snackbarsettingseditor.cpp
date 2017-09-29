#include "snackbarsettingseditor.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include "qtmaterialsnackbar.h"

SnackbarSettingsEditor::SnackbarSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::SnackbarSettingsForm),
      m_snackbar(new QtMaterialSnackbar)
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
    canvas->setMaximumHeight(300);

//    layout->addWidget(m_snackbar);
//    layout->setAlignment(m_snackbar, Qt::AlignHCenter);

//    setupForm();

//    connect(ui->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
//    connect(ui->valueLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
//    connect(ui->orientationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
//    connect(ui->invertedCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
//
//    connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(setupForm()));
}

SnackbarSettingsEditor::~SnackbarSettingsEditor()
{
    delete ui;
}

void SnackbarSettingsEditor::setupForm()
{
//    switch (m_slider->orientation())
//    {
//    case Qt::Horizontal:
//        ui->orientationComboBox->setCurrentIndex(0);
//        break;
//    case Qt::Vertical:
//        ui->orientationComboBox->setCurrentIndex(1);
//        break;
//    default:
//        break;
//    }
//
//    ui->disabledCheckBox->setChecked(!m_slider->isEnabled());
//    ui->valueLineEdit->setText(QString::number(m_slider->value()));
//    ui->invertedCheckBox->setChecked(m_slider->invertedAppearance());
}

void SnackbarSettingsEditor::updateWidget()
{
//    switch (ui->orientationComboBox->currentIndex())
//    {
//    case 0:
//        m_slider->setOrientation(Qt::Horizontal);
//        break;
//    case 1:
//        m_slider->setOrientation(Qt::Vertical);
//        break;
//    default:
//        break;
//    }
//
//    m_slider->setDisabled(ui->disabledCheckBox->isChecked());
//    m_slider->setValue(ui->valueLineEdit->text().toInt());
//    m_slider->setInvertedAppearance(ui->invertedCheckBox->isChecked());
}
