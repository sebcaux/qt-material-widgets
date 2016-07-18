#include "slidersettingseditor.h"
#include <QVBoxLayout>
#include <QSlider>
#include "xx/qtmaterialslider.h"
#include "components/slider.h"

SliderSettingsEditor::SliderSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::SliderSettingsForm),
      m_slider(new QtMaterialSlider)
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
    layout->addWidget(m_slider);
//    layout->addWidget(new QSlider(Qt::Horizontal));
//    layout->addWidget(new Slider);

    setupForm();
}

SliderSettingsEditor::~SliderSettingsEditor()
{
    delete ui;
}

void SliderSettingsEditor::setupForm()
{
}

void SliderSettingsEditor::updateWidget()
{
}

void SliderSettingsEditor::selectColor()
{
}

