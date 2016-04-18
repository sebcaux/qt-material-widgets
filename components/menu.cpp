#include <QWidget>
#include <QVBoxLayout>
#include <QPainter>
#include "menu.h"

MenuItem::MenuItem(QWidget *parent)
    : FlatButton(parent)
{
    setMinimumHeight(40);
}

MenuItem::MenuItem(const QString &text, QWidget *parent)
    : FlatButton(text, parent)
{
    setMinimumHeight(40);
}

MenuItem::~MenuItem()
{
}

Menu::Menu(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    layout->setMargin(0);
    layout->setSpacing(0);

    QSizePolicy policy;
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    policy.setVerticalPolicy(QSizePolicy::Maximum);
    setSizePolicy(policy);

    layout->addWidget(new MenuItem("Item #1"));
    layout->addWidget(new MenuItem("Item #2"));
    layout->addWidget(new MenuItem("Item #3"));
    layout->addWidget(new MenuItem("Item #4"));
}

Menu::~Menu()
{
}

void Menu::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.fillRect(rect(), Qt::white);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    QWidget::paintEvent(event);
}
