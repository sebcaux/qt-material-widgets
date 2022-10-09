#ifndef SETTINGSEDITOR_H
#define SETTINGSEDITOR_H

#include <QWidget>

#include <QScrollArea>

class QLineEdit;

class SettingsEditor : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsEditor(QWidget *parent = nullptr);

protected:
    QScrollArea *_settingsScrollArea;
    QWidget *_settingsWidget;
    QWidget *_canvas;

    void setLineEditColor(QLineEdit *lineEdit, const QColor &color);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
    QSize sizeHint() const override;
};

#endif  // SETTINGSEDITOR_H
