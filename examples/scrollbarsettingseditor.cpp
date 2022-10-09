#include "scrollbarsettingseditor.h"

#include <QColorDialog>
#include <QTextEdit>
#include <QVBoxLayout>

#include <qtmaterialscrollbar.h>

ScrollBarSettingsEditor::ScrollBarSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::ScrollBarSettingsForm),
      m_verticalScrollbar(new QtMaterialScrollBar),
      m_horizontalScrollbar(new QtMaterialScrollBar)
{
    ui->setupUi(_settingsWidget);

    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);

    QTextEdit *edit = new QTextEdit;
    edit->setText("<p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of "
                  "syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the "
                  "study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The "
                  "distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax "
                  "and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study "
                  "of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p>"
                  "<p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of "
                  "syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the "
                  "study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The "
                  "distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax "
                  "and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study "
                  "of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p>");
    edit->setLineWrapMode(QTextEdit::NoWrap);
    edit->update();
    edit->setMaximumHeight(200);

    edit->setVerticalScrollBar(m_verticalScrollbar);
    edit->setHorizontalScrollBar(m_horizontalScrollbar);

    // m_verticalScrollbar->setHideOnMouseOut(false);

    // m_horizontalScrollbar->setHideOnMouseOut(false);
    m_horizontalScrollbar->setOrientation(Qt::Horizontal);

    layout->addWidget(edit);
    layout->setAlignment(edit, Qt::AlignHCenter);

    setupForm();

    connect(ui->hideCheckBox, &QAbstractButton::toggled, this, &ScrollBarSettingsEditor::updateWidget);
    connect(ui->useThemeColorsCheckBox, &QAbstractButton::toggled, this, &ScrollBarSettingsEditor::updateWidget);
    connect(ui->canvasColorToolButton, &QAbstractButton::clicked, this, &ScrollBarSettingsEditor::selectColor);
    connect(ui->backgroundColorToolButton, &QAbstractButton::clicked, this, &ScrollBarSettingsEditor::selectColor);
    connect(ui->sliderColorToolButton, &QAbstractButton::clicked, this, &ScrollBarSettingsEditor::selectColor);
}

ScrollBarSettingsEditor::~ScrollBarSettingsEditor()
{
    delete ui;
}

void ScrollBarSettingsEditor::setupForm()
{
    ui->hideCheckBox->setChecked(m_verticalScrollbar->hideOnMouseOut());
    ui->useThemeColorsCheckBox->setChecked(m_verticalScrollbar->useThemeColors());
    setLineEditColor(ui->canvasColorLineEdit, m_verticalScrollbar->canvasColor());
    setLineEditColor(ui->backgroundColorLineEdit, m_verticalScrollbar->backgroundColor());
    setLineEditColor(ui->sliderColorLineEdit, m_verticalScrollbar->sliderColor());
}

void ScrollBarSettingsEditor::updateWidget()
{
    m_verticalScrollbar->setHideOnMouseOut(ui->hideCheckBox->isChecked());
    m_horizontalScrollbar->setHideOnMouseOut(ui->hideCheckBox->isChecked());

    m_verticalScrollbar->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    m_horizontalScrollbar->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
}

void ScrollBarSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec() != 0)
    {
        QColor color = dialog.selectedColor();
        if (sender() == ui->canvasColorToolButton)
        {
            m_verticalScrollbar->setCanvasColor(color);
            m_horizontalScrollbar->setCanvasColor(color);
        }
        else if (sender() == ui->backgroundColorToolButton)
        {
            m_verticalScrollbar->setBackgroundColor(color);
            m_horizontalScrollbar->setBackgroundColor(color);
        }
        else if (sender() == ui->sliderColorToolButton)
        {
            m_verticalScrollbar->setSliderColor(color);
            m_horizontalScrollbar->setSliderColor(color);
        }
        ui->useThemeColorsCheckBox->setChecked(false);
    }
    setupForm();
}
