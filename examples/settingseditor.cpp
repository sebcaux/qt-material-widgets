#include "settingseditor.h"

#include <QResizeEvent>

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
