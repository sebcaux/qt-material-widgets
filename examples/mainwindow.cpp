#include "mainwindow.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QListWidget>
#include "avatarsettingseditor.h"
#include "badgesettingseditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    widget->setLayout(layout);

    QStackedLayout *stack = new QStackedLayout;
    QListWidget *list = new QListWidget;

    setCentralWidget(widget);

    layout->addWidget(list);
    layout->addLayout(stack);

    layout->setStretch(1, 2);

    AvatarSettingsEditor *avatar = new AvatarSettingsEditor;
    BadgeSettingsEditor *badge = new BadgeSettingsEditor;

    stack->addWidget(avatar);
    stack->addWidget(badge);

    list->addItem("Avatar");
    list->addItem("Badge");

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
