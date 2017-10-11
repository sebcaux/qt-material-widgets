#include "appbarsettingseditor.h"
#include <QtWidgets/QVBoxLayout>
#include <qtmaterialappbar.h>
#include <lib/qtmaterialtheme.h>

AppBarSettingsEditor::AppBarSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::AppBarSettingsForm),
      m_appBar(new QtMaterialAppBar)
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
    layout->addStretch(1);

    setupForm();
}

AppBarSettingsEditor::~AppBarSettingsEditor()
{
    delete ui;
}

void AppBarSettingsEditor::setupForm()
{
}

void AppBarSettingsEditor::updateWidget()
{
}
