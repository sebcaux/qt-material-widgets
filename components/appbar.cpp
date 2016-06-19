#include "appbar.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include "lib/customshadoweffect.h"

AppBar::AppBar(QWidget *parent)
    : QWidget(parent)
{
    CustomShadowEffect *effect = new CustomShadowEffect;
    effect->setDistance(3);
    effect->setBlurRadius(11);
    effect->setColor(QColor(0, 0, 0, 50));
    setGraphicsEffect(effect);

    QHBoxLayout *layout = new QHBoxLayout;
    setLayout(layout);

    QLabel *label = new QLabel("App");
    layout->addWidget(label);

    QFont font(this->font());
    font.setPointSizeF(18);
    label->setFont(font);

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
