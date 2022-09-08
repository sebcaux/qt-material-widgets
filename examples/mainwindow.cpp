#include "mainwindow.h"

#include <QHBoxLayout>
#include <QListWidget>
#include <QSplitter>
#include <QStackedLayout>

#include "appbarsettingseditor.h"
#include "autocompletesettingseditor.h"
#include "avatarsettingseditor.h"
#include "badgesettingseditor.h"
#include "checkboxsettingseditor.h"
#include "circularprogresssettingseditor.h"
#include "dialogsettingseditor.h"
#include "drawersettingseditor.h"
#include "fabsettingseditor.h"
#include "flatbuttonsettingseditor.h"
#include "iconbuttonsettingseditor.h"
#include "progresssettingseditor.h"
#include "radiobuttonsettingseditor.h"
#include "scrollbarsettingseditor.h"
#include "slidersettingseditor.h"
#include "snackbarsettingseditor.h"
#include "tabssettingseditor.h"
#include "textfieldsettingseditor.h"
#include "togglesettingseditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QListWidget *list = new QListWidget;
    list->setMaximumWidth(300);

    QWidget *stackWidget = new QWidget;
    QStackedLayout *stackLayout = new QStackedLayout;
    stackWidget->setLayout(stackLayout);

    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(list);
    splitter->addWidget(stackWidget);

    setCentralWidget(splitter);

    AvatarSettingsEditor *avatar = new AvatarSettingsEditor;
    BadgeSettingsEditor *badge = new BadgeSettingsEditor;
    CheckBoxSettingsEditor *checkbox = new CheckBoxSettingsEditor;
    FloatingActionButtonSettingsEditor *fab = new FloatingActionButtonSettingsEditor;
    FlatButtonSettingsEditor *flatButton = new FlatButtonSettingsEditor;
    IconButtonSettingsEditor *iconButton = new IconButtonSettingsEditor;
    ProgressSettingsEditor *progress = new ProgressSettingsEditor;
    CircularProgressSettingsEditor *circularProgress = new CircularProgressSettingsEditor;
    SliderSettingsEditor *slider = new SliderSettingsEditor;
    RadioButtonSettingsEditor *radioButton = new RadioButtonSettingsEditor;
    ToggleSettingsEditor *toggle = new ToggleSettingsEditor;
    TextFieldSettingsEditor *textField = new TextFieldSettingsEditor;
    TabsSettingsEditor *tabs = new TabsSettingsEditor;
    SnackbarSettingsEditor *snackbar = new SnackbarSettingsEditor;
    DialogSettingsEditor *dialog = new DialogSettingsEditor;
    DrawerSettingsEditor *drawer = new DrawerSettingsEditor;
    ScrollBarSettingsEditor *scrollBar = new ScrollBarSettingsEditor;
    AppBarSettingsEditor *appBar = new AppBarSettingsEditor;
    AutoCompleteSettingsEditor *autocomplete = new AutoCompleteSettingsEditor;

    stackLayout->addWidget(appBar);
    stackLayout->addWidget(autocomplete);
    stackLayout->addWidget(avatar);
    stackLayout->addWidget(badge);
    stackLayout->addWidget(checkbox);
    stackLayout->addWidget(circularProgress);
    stackLayout->addWidget(dialog);
    stackLayout->addWidget(drawer);
    stackLayout->addWidget(fab);
    stackLayout->addWidget(flatButton);
    stackLayout->addWidget(iconButton);
    stackLayout->addWidget(progress);
    stackLayout->addWidget(radioButton);
    stackLayout->addWidget(scrollBar);
    stackLayout->addWidget(slider);
    stackLayout->addWidget(snackbar);
    stackLayout->addWidget(tabs);
    stackLayout->addWidget(textField);
    stackLayout->addWidget(toggle);

    list->addItem(tr("App Bar"));
    list->addItem(tr("Auto Complete"));
    list->addItem(tr("Avatar"));
    list->addItem(tr("Badge"));
    list->addItem(tr("Checkbox"));
    list->addItem(tr("Circular Progress"));
    list->addItem(tr("Dialog"));
    list->addItem(tr("Drawer"));
    list->addItem(tr("Floating Action Button"));
    list->addItem(tr("Flat Button"));
    list->addItem(tr("Icon Button"));
    list->addItem(tr("Progress"));
    list->addItem(tr("Radio Button"));
    list->addItem(tr("ScrollBar"));
    list->addItem(tr("Slider"));
    list->addItem(tr("Snackbar"));
    list->addItem(tr("Tabs"));
    list->addItem(tr("Text Field"));
    list->addItem(tr("Toggle"));

    QObject::connect(list,
                     &QListWidget::currentItemChanged,
                     this,
                     [=](QListWidgetItem *current, QListWidgetItem *previous)
                     {
                         Q_UNUSED(current)
                         Q_UNUSED(previous)
                         stackLayout->setCurrentIndex(list->currentRow());
                     });

    list->setCurrentRow(0);
}

MainWindow::~MainWindow()
{
}
