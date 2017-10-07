#include "drawersettingseditor.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include <qtmaterialdrawer.h>

DrawerSettingsEditor::DrawerSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::DrawerSettingsForm),
      m_drawer(new QtMaterialDrawer)
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

    m_drawer->setParent(this);
    m_drawer->setClickOutsideToClose(true);
    m_drawer->setOverlayMode(true);

    setupForm();

    connect(ui->showDrawerButton, SIGNAL(pressed()), m_drawer, SLOT(openDrawer()));
    connect(ui->hideDrawerButton, SIGNAL(pressed()), m_drawer, SLOT(closeDrawer()));
}

DrawerSettingsEditor::~DrawerSettingsEditor()
{
    delete ui;
}

void DrawerSettingsEditor::setupForm()
{
}

void DrawerSettingsEditor::updateWidget()
{
}
