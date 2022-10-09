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

    m_snackbar->setParent(this);

    setupForm();

    connect(ui->showSnackbarButton, &QAbstractButton::pressed, this, &SnackbarSettingsEditor::showSnackbar);
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
    m_snackbar->addMessage(tr("Snack attack!"));
}
