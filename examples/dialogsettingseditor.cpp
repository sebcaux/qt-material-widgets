#include "dialogsettingseditor.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include "qtmaterialdialog.h"

DialogSettingsEditor::DialogSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::DialogSettingsForm),
      m_dialog(new QtMaterialDialog)
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
    layout->addWidget(m_dialog);
    layout->setAlignment(m_dialog, Qt::AlignHCenter);

    m_dialog->setParent(this);

    QWidget *dialogWidget = new QWidget;
    QVBoxLayout *dialogWidgetLayout = new QVBoxLayout;
    dialogWidget->setLayout(dialogWidgetLayout);

    QPushButton *closeButton = new QPushButton("Close");
    dialogWidgetLayout->addWidget(closeButton);

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
