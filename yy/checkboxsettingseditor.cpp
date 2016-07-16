#include "yy/checkboxsettingseditor.h"
#include <QVBoxLayout>
#include <QColorDialog>
//#include "components/checkbox.h"
#include "xxlib/qtmaterialcheckable.h"

CheckBoxSettingsEditor::CheckBoxSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::CheckBoxSettingsForm),
      m_checkBox(new QtMaterialCheckable)
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

    m_checkBox->setText("Palak paneer");

    layout = new QVBoxLayout;
    canvas->setLayout(layout);
    layout->addWidget(m_checkBox);
    layout->setAlignment(m_checkBox, Qt::AlignCenter);

    setupForm();
}

CheckBoxSettingsEditor::~CheckBoxSettingsEditor()
{
    delete ui;
}

void CheckBoxSettingsEditor::setupForm()
{
}

void CheckBoxSettingsEditor::updateWidget()
{
}

void CheckBoxSettingsEditor::selectColor()
{
}
