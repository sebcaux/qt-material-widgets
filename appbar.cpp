#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include "appbar.h"

AppBar::AppBar(QWidget *parent)
    : QWidget(parent)
{
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setOffset(0, 2);
    effect->setBlurRadius(11);
    effect->setColor(QColor(0, 0, 0, 50));
    setGraphicsEffect(effect);

    QHBoxLayout *layout = new QHBoxLayout;
    setLayout(layout);

    QLabel *label = new QLabel("App");
    layout->addWidget(label);

    setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum));

    setMinimumHeight(64);
}

AppBar::~AppBar()
{
}

void AppBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);

    painter.fillRect(rect(), brush);
}
