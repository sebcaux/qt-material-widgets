#include "mainwindow.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QListWidget>
#include "avatarsettingseditor.h"
#include "badgesettingseditor.h"
#include "checkboxsettingseditor.h"
#include "fabsettingseditor.h"
#include "raisedbuttonsettingseditor.h"
#include "flatbuttonsettingseditor.h"
#include "iconbuttonsettingseditor.h"
#include "progresssettingseditor.h"
#include "circularprogresssettingseditor.h"
#include "slidersettingseditor.h"
#include "radiobuttonsettingseditor.h"
#include "togglesettingseditor.h"
#include "textfieldsettingseditor.h"
#include "tabssettingseditor.h"
#include "selectfieldsettingseditor.h"
#include "iconmenusettingseditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    widget->setLayout(layout);

    QStackedLayout *stack = new QStackedLayout;
    QListWidget *list = new QListWidget;

    layout->addWidget(list);
    layout->addLayout(stack);

    layout->setStretch(1, 2);

    setCentralWidget(widget);

    AvatarSettingsEditor *avatar = new AvatarSettingsEditor;
    BadgeSettingsEditor *badge = new BadgeSettingsEditor;
    CheckBoxSettingsEditor *checkbox = new CheckBoxSettingsEditor;
    FloatingActionButtonSettingsEditor *fab = new FloatingActionButtonSettingsEditor;
    RaisedButtonSettingsEditor *raisedButton = new RaisedButtonSettingsEditor;
    FlatButtonSettingsEditor *flatButton = new FlatButtonSettingsEditor;
    IconButtonSettingsEditor *iconButton = new IconButtonSettingsEditor;
    ProgressSettingsEditor *progress = new ProgressSettingsEditor;
    CircularProgressSettingsEditor *circularProgress = new CircularProgressSettingsEditor;
    SliderSettingsEditor *slider = new SliderSettingsEditor;
    RadioButtonSettingsEditor *radioButton = new RadioButtonSettingsEditor;
    ToggleSettingsEditor *toggle = new ToggleSettingsEditor;
    TextFieldSettingsEditor *textField = new TextFieldSettingsEditor;
    TabsSettingsEditor *tabs = new TabsSettingsEditor;
    SelectFieldSettingsEditor *selectField = new SelectFieldSettingsEditor;
    IconMenuSettingsEditor *iconMenu = new IconMenuSettingsEditor;

    stack->addWidget(avatar);
    stack->addWidget(badge);
    stack->addWidget(checkbox);
    stack->addWidget(circularProgress);
    stack->addWidget(fab);
    stack->addWidget(flatButton);
    stack->addWidget(iconButton);
    stack->addWidget(iconMenu);
    stack->addWidget(progress);
    stack->addWidget(radioButton);
    stack->addWidget(raisedButton);
    stack->addWidget(selectField);
    stack->addWidget(slider);
    stack->addWidget(tabs);
    stack->addWidget(textField);
    stack->addWidget(toggle);

    list->addItem("Avatar");
    list->addItem("Badge");
    list->addItem("Checkbox");
    list->addItem("Circular Progress");
    list->addItem("Floating Action Button");
    list->addItem("Flat Button");
    list->addItem("Icon Button");
    list->addItem("Icon Menu");
    list->addItem("Progress");
    list->addItem("Radio Button");
    list->addItem("Raised Button");
    list->addItem("Select Field");
    list->addItem("Slider");
    list->addItem("Tabs");
    list->addItem("Text Field");
    list->addItem("Toggle");

    list->setCurrentRow(0);

    QObject::connect(list,  &QListWidget::currentItemChanged,
        [=](QListWidgetItem *current, QListWidgetItem *previous)
    {
        Q_UNUSED(current)
        Q_UNUSED(previous)
        stack->setCurrentIndex(list->currentRow());
    });
}

MainWindow::~MainWindow()
{
}
