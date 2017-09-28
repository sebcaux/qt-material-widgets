#include "mainwindow.h"
#include <QtWidgets/QVBoxLayout>
#include "avatarsettingseditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    AvatarSettingsEditor *editor = new AvatarSettingsEditor;
    setCentralWidget(editor);
}

MainWindow::~MainWindow()
{
}
