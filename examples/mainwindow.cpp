#include "mainwindow.h"
#include <QtWidgets/QVBoxLayout>
#include "avatarsettingseditor.h"
#include "badgesettingseditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    AvatarSettingsEditor *editor = new AvatarSettingsEditor;
    setCentralWidget(editor);

    //BadgeSettingsEditor *editor = new BadgeSettingsEditor;
    //setCentralWidget(editor);
}

MainWindow::~MainWindow()
{
}
