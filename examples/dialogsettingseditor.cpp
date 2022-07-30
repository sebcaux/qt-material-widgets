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

    //_canvas->setMaximumHeight(300);

    m_dialog->setParent(_canvas);

    QWidget *dialogWidget = new QWidget;
    QVBoxLayout *dialogWidgetLayout = new QVBoxLayout;
    dialogWidget->setLayout(dialogWidgetLayout);

    QtMaterialFlatButton *closeButton = new QtMaterialFlatButton("Close");
    dialogWidgetLayout->addWidget(closeButton);
    dialogWidgetLayout->setAlignment(closeButton, Qt::AlignBottom | Qt::AlignCenter);

    closeButton->setMaximumWidth(150);

    QVBoxLayout *dialogLayout = new QVBoxLayout;
    m_dialog->setWindowLayout(dialogLayout);

    dialogWidget->setMinimumHeight(300);

    dialogLayout->addWidget(dialogWidget);

    setupForm();

    connect(ui->showDialogButton, SIGNAL(pressed()), m_dialog, SLOT(showDialog()));
    connect(closeButton, SIGNAL(pressed()), m_dialog, SLOT(hideDialog()));
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
