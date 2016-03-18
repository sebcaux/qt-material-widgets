#include <QVBoxLayout>
#include <QPushButton>
#include "mainwindow.h"
#include "flatbutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);

    QPushButton *button1 = new QPushButton("Test #1");
    layout->addWidget(button1);

    FlatButton *flatButton = new FlatButton;
    flatButton->setText("My button");
    layout->addWidget(flatButton);
    flatButton->setMinimumHeight(40);

    QPushButton *button2 = new QPushButton("Test #2");
    layout->addWidget(button2);
}

MainWindow::~MainWindow()
{
}
