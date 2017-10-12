#ifndef AUTOCOMPLETESETTINGSEDITOR_H
#define AUTOCOMPLETESETTINGSEDITOR_H

#include <QWidget>
//#include "ui_autocompletesettingsform.h"

#include "lib/qtmaterialoverlaywidget.h"

class QtMaterialAutoComplete;

class AutoCompleteSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit AutoCompleteSettingsEditor(QWidget *parent = 0);
    ~AutoCompleteSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    //Ui::AutoCompleteSettingsForm *const ui;
    QtMaterialAutoComplete       *const m_autocomplete;
};

class Menu;

class Xyz : public QtMaterialOverlayWidget
{
    Q_OBJECT

public:
    explicit Xyz(QtMaterialAutoComplete *input, QWidget *parent = 0);
    ~Xyz();

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QtMaterialAutoComplete *const m_input;
    Menu                   *const m_menu;
};

class Menu : public QWidget
{
    Q_OBJECT

public:
    Menu(QWidget *parent = 0);
    ~Menu();

    //QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};

#endif // AUTOCOMPLETESETTINGSEDITOR_H
