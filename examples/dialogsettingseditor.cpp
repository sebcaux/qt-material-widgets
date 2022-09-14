#include "dialogsettingseditor.h"

#include <QColorDialog>
#include <QVBoxLayout>

#include <qtmaterialdialog.h>
#include <qtmaterialflatbutton.h>

DialogSettingsEditor::DialogSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::DialogSettingsForm),
      m_dialog(new QtMaterialDialog)
{
    ui->setupUi(_settingsWidget);

    m_dialog->setParent(_canvas);

    QWidget *dialogWidget = new QWidget;
    QVBoxLayout *dialogWidgetLayout = new QVBoxLayout;

    dialogWidgetLayout->addWidget(new QLabel(tr("This is a beautiful material design dialog, don't you think ?")));
    dialogWidgetLayout->addStretch(1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;

    QtMaterialFlatButton *okButton = new QtMaterialFlatButton(tr("OK"), Material::ButtonRaisedPrimary);
    buttonsLayout->addWidget(okButton);
    okButton->setMaximumWidth(150);

    QtMaterialFlatButton *cancelButton = new QtMaterialFlatButton(tr("Cancel"), Material::ButtonOutlinedSecondary);
    buttonsLayout->addWidget(cancelButton);
    cancelButton->setMaximumWidth(150);

    dialogWidgetLayout->addItem(buttonsLayout);
    dialogWidget->setLayout(dialogWidgetLayout);

    QVBoxLayout *dialogLayout = new QVBoxLayout;
    dialogWidget->setMinimumHeight(300);
    dialogLayout->addWidget(dialogWidget);
    m_dialog->setWindowLayout(dialogLayout);

    setupForm();

    connect(ui->showDialogButton, &QAbstractButton::clicked, m_dialog, &QtMaterialDialog::showDialog);
    connect(cancelButton, &QAbstractButton::clicked, m_dialog, &QtMaterialDialog::hideDialog);
}

DialogSettingsEditor::~DialogSettingsEditor()
{
    delete ui;
}

void DialogSettingsEditor::setupForm()
{
}

void DialogSettingsEditor::updateWidget()
{
}
