#ifndef SETTINGSEDITOR_H
#define SETTINGSEDITOR_H

#include <QWidget>

class SettingsEditor : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsEditor(QWidget *parent = nullptr);

protected:
    QWidget *_settingsWidget;
    QWidget *_canvas;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
    QSize sizeHint() const override;
};

#endif  // SETTINGSEDITOR_H
