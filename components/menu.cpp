#include "menu.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

MenuItem::MenuItem(QWidget *parent)
    : FlatButton(parent)
{
    //QFont font(this->font());
    //font.setCapitalization(QFont::MixedCase);
    //font.setPointSize(11);
    //font.setStyleName("Regular");
    //setFont(font);

    setShowHalo(false);
}

MenuItem::MenuItem(const QString &text, QWidget *parent)
    : FlatButton(text, parent)
{
    //QFont font(this->font());
    //font.setCapitalization(QFont::MixedCase);
    //font.setPointSize(11);
    //font.setStyleName("Regular");
    //setFont(font);

    setShowHalo(false);
}

MenuItem::~MenuItem()
{
}

QSize MenuItem::sizeHint() const
{
    return FlatButton::sizeHint().expandedTo(QSize(200, 50));
}

Menu::Menu(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    layout->setMargin(0);
    layout->setSpacing(0);

    //QSizePolicy policy;
    //policy.setVerticalPolicy(QSizePolicy::Maximum);
    //setSizePolicy(policy);

//    QSizePolicy policy(QSizePolicy::MinimumExpanding,
//                       QSizePolicy::MinimumExpanding);
//    setSizePolicy(policy);

    //QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    //effect->setBlurRadius(9);
    //effect->setOffset(QPoint(0, 0));
    //effect->setColor(QColor(0, 0, 0, 100));
    //setGraphicsEffect(effect);
}

Menu::~Menu()
{
}

void Menu::addMenuItem(MenuItem *item)
{
    m_items.push_back(item);
    layout()->addWidget(item);
}

void Menu::addMenuItem(const QString &text)
{
    addMenuItem(new MenuItem(text));
}

void Menu::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
}
