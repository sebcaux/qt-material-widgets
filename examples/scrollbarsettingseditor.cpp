#include "scrollbarsettingseditor.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include <QtWidgets/QTextEdit>
#include <qtmaterialscrollbar.h>

ScrollBarSettingsEditor::ScrollBarSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::ScrollBarSettingsForm),
      m_scrollbar(new QtMaterialScrollBar)
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
    canvas->setMaximumHeight(400);

    QTextEdit *edit = new QTextEdit;
    edit->setText("<p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p>");
    edit->update();
    edit->setMaximumHeight(200);

    edit->setVerticalScrollBar(m_scrollbar);
    m_scrollbar->setHideOnMouseOut(false);

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
