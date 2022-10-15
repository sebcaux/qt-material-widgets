#include "settingseditor.h"

#include <QLineEdit>
#include <QResizeEvent>

#include "lib/qtmaterialstyle.h"
#include "qtmaterialcanvas.h"

SettingsEditor::SettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(QSize(640, 480));

    _settingsScrollArea = new QScrollArea(this);
    _settingsWidget = new QWidget(this);
    _settingsScrollArea->setWidgetResizable(true);
    _settingsScrollArea->setWidget(_settingsWidget);

    _canvas = new QtMaterialCanvas(this);

    connect(&QtMaterialStyle::instance(), &QtMaterialStyle::themeChanged, this, &SettingsEditor::setupForm);
}

void SettingsEditor::setupForm()
{
}

void SettingsEditor::updateWidget()
{
}

void SettingsEditor::setLineEditColor(QLineEdit *lineEdit, const QColor &color)
{
    lineEdit->setText(color.name(QColor::HexRgb).toUpper());

    QPalette p = lineEdit->palette();
    p.setColor(QPalette::Base, color);
    if (color.lightness() < 128)
    {
        p.setColor(QPalette::Text, Qt::white);
    }
    else
    {
        p.setColor(QPalette::Text, Qt::black);
    }

    lineEdit->setPalette(p);
}

void SettingsEditor::resizeEvent(QResizeEvent *event)
{
    _settingsScrollArea->setGeometry(0, 0, event->size().width(), event->size().height() / 2);
    _canvas->setGeometry(0, event->size().height() / 2, event->size().width(), event->size().height() / 2);
}

QSize SettingsEditor::sizeHint() const
{
    return QSize(640, 480);
}
