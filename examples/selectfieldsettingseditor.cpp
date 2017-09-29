#include "yy/selectfieldsettingseditor.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QColorDialog>
#include "xx/qtmaterialselectfield.h"
#include "xx/qtmaterialmenuitem.h"

SelectFieldSettingsEditor::SelectFieldSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::SelectFieldSettingsForm),
      m_selectField(new QtMaterialSelectField)
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
    layout->addWidget(m_selectField);
    layout->setAlignment(m_selectField, Qt::AlignCenter);

    m_selectField->setPlaceholderText("Please select your favorite language");

    {
        m_selectField->addItem("C");
        m_selectField->addItem("C++");
        m_selectField->addItem("PHP");
        m_selectField->addItem("Haskell");
        m_selectField->addItem("JavaScript");
        m_selectField->addItem("ECMAScript");
        m_selectField->addItem("OCaml");
        m_selectField->addItem("Python");
        m_selectField->addItem("F#");
        m_selectField->addItem("Clojure");
        m_selectField->addItem("Java");

        m_selectField->itemAt(2)->setDisabled(true);
    }

    setupForm();

    connect(ui->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->foregroundColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->underlineColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->placeholderColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->highlightedColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->disabledColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->placeholderLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(ui->clearSelectionToolButton, SIGNAL(clicked(bool)), m_selectField, SLOT(clearSelection()));
}

SelectFieldSettingsEditor::~SelectFieldSettingsEditor()
{
    delete ui;
}

void SelectFieldSettingsEditor::setupForm()
{
    ui->disabledCheckBox->setChecked(!m_selectField->isEnabled());
    ui->useThemeColorsCheckBox->setChecked(m_selectField->useThemeColors());
    ui->placeholderLineEdit->setText(m_selectField->placeholderText());
}

void SelectFieldSettingsEditor::updateWidget()
{
    m_selectField->setDisabled(ui->disabledCheckBox->isChecked());
    m_selectField->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    m_selectField->setPlaceholderText(ui->placeholderLineEdit->text());
}

void SelectFieldSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("foregroundColorToolButton" == senderName) {
            m_selectField->setForegroundColor(color);
            ui->foregroundColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("underlineColorToolButton" == senderName) {
            m_selectField->setUnderlineColor(color);
            ui->underlineColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("placeholderColorToolButton" == senderName) {
            m_selectField->setPlaceholderColor(color);
            ui->placeholderColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("highlightedColorToolButton" == senderName) {
            m_selectField->setHighlightedColor(color);
            ui->highlightedColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("disabledColorToolButton" == senderName) {
            m_selectField->setDisabledColor(color);
            ui->disabledColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
