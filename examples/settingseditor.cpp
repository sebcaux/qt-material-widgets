#include "settingseditor.h"

#include <QLineEdit>
#include <QResizeEvent>
#include <QVBoxLayout>

#include "lib/qtmaterialstyle.h"
#include "qtmaterialcanvas.h"

SettingsEditor::SettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(QSize(640, 480));

    QVBoxLayout *layout = new QVBoxLayout(this);

    _settingsScrollArea = new QScrollArea(this);
    _settingsWidget = new QWidget(this);
    _settingsScrollArea->setWidgetResizable(true);
    _settingsScrollArea->setWidget(_settingsWidget);
    layout->addWidget(_settingsScrollArea);

    _canvas = new QtMaterialCanvas(this);
    layout->addWidget(_canvas);

    connect(&QtMaterialStyle::instance(), &QtMaterialStyle::themeChanged, this, &SettingsEditor::setupForm);

    setLayout(layout);
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

QSize SettingsEditor::sizeHint() const
{
    return QSize(640, 480);
}
