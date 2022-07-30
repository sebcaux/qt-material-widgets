#include "settingseditor.h"

#include <QResizeEvent>

SettingsEditor::SettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(QSize(400, 300));

    _settingsWidget = new QWidget(this);

    _canvas = new QWidget(this);
    _canvas->setStyleSheet("QWidget { background: white; }");
}

void SettingsEditor::resizeEvent(QResizeEvent *event)
{
    _settingsWidget->setGeometry(0, 0, event->size().width(), event->size().height() / 2);
    _canvas->setGeometry(0, event->size().height() / 2, event->size().width(), event->size().height() / 2);
}

QSize SettingsEditor::sizeHint() const
{
    return QSize(400, 300);
}
