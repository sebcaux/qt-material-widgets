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
    //_canvas->setMaximumHeight(400);

    QTextEdit *edit = new QTextEdit;
    edit->setText("<p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of "
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
}

ScrollBarSettingsEditor::~ScrollBarSettingsEditor()
{
    delete ui;
}

void ScrollBarSettingsEditor::setupForm()
{
}

void ScrollBarSettingsEditor::updateWidget()
{
}
