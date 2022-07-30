#include "snackbarsettingseditor.h"

#include <QColorDialog>
#include <QVBoxLayout>

#include <qtmaterialsnackbar.h>

SnackbarSettingsEditor::SnackbarSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::SnackbarSettingsForm),
      m_snackbar(new QtMaterialSnackbar)
{
    ui->setupUi(_settingsWidget);

    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);
    //_canvas->setMaximumHeight(300);

    m_snackbar->setParent(this);

    setupForm();

    connect(ui->showSnackbarButton, SIGNAL(pressed()), this, SLOT(showSnackbar()));
}

SnackbarSettingsEditor::~SnackbarSettingsEditor()
{
    delete ui;
}

void SnackbarSettingsEditor::setupForm()
{
}

void SnackbarSettingsEditor::updateWidget()
{
}

void SnackbarSettingsEditor::showSnackbar()
{
    m_snackbar->addMessage(QString("Snack attack!"));
}
