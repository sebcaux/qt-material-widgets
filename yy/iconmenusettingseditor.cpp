#include "yy/iconmenusettingseditor.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QColorDialog>
#include "xx/qtmaterialiconmenu.h"
#include "xx/qtmaterialmenuitem.h"

IconMenuSettingsEditor::IconMenuSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::IconMenuSettingsForm),
      m_iconMenu(new QtMaterialIconMenu(QIcon("../qt-material-widgets/ic_star_black_24px.svg")))
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
    layout->addWidget(m_iconMenu);
    layout->setAlignment(m_iconMenu, Qt::AlignCenter);

    {
        m_iconMenu->addMenuItem("C");
        m_iconMenu->addMenuItem("C++");
        m_iconMenu->addMenuItem("PHP");
        m_iconMenu->addMenuItem("Haskell");
        m_iconMenu->addMenuItem("JavaScript");
        m_iconMenu->addMenuItem("ECMAScript");
        m_iconMenu->addMenuItem("OCaml");
        m_iconMenu->addMenuItem("Python");
        m_iconMenu->addMenuItem("F#");
        m_iconMenu->addMenuItem("Clojure");
        m_iconMenu->addMenuItem("Java");

        m_iconMenu->itemAt(2)->setDisabled(true);
    }

    setupForm();

    connect(ui->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->autoCollapseCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->colorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->disabledColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
}

IconMenuSettingsEditor::~IconMenuSettingsEditor()
{
    delete ui;
}

void IconMenuSettingsEditor::setupForm()
{
    ui->disabledCheckBox->setChecked(!m_iconMenu->isEnabled());
    ui->autoCollapseCheckBox->setChecked(m_iconMenu->autoCollapse());
}

void IconMenuSettingsEditor::updateWidget()
{
    m_iconMenu->setDisabled(ui->disabledCheckBox->isChecked());
    m_iconMenu->setAutoCollapse(ui->autoCollapseCheckBox->isChecked());
}

void IconMenuSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("colorToolButton" == senderName) {
            m_iconMenu->setColor(color);
            ui->colorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("disabledColorToolButton" == senderName) {
            m_iconMenu->setDisabledColor(color);
            ui->disabledColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
