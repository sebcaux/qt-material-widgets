#include <QWidget>
#include <QPainter>
#include <QIcon>
#include "avatar.h"
#include "avatar_p.h"

AvatarPrivate::AvatarPrivate(Avatar *q)
    : q_ptr(q),
      size(40)
{
}

void AvatarPrivate::init()
{
    Q_Q(Avatar);

    QFont font(q->font());
    font.setPointSizeF(16);
    q->setFont(font);
}

Avatar::Avatar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new AvatarPrivate(this))
{
    d_func()->init();
}

Avatar::~Avatar()
{
}

void Avatar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);

    QRect r = rect();
    painter.drawEllipse(r.center(), 20, 20);

    //painter.setPen(textColor());
    painter.setPen(Qt::white);
    painter.setBrush(Qt::NoBrush);
    painter.drawText(r.translated(0, -1), Qt::AlignCenter, "A");

    return;//
    QIcon icon("../qt-material-widgets/ic_message_white_24px.svg");

    icon.paint(&painter,
               QRect(width()/2-10, height()/2-10, 20, 20),
               Qt::AlignCenter,
               QIcon::Normal);

    //

    QImage img("../qt-material-widgets/uxceo-128.jpg");

    QPixmap pm = QPixmap::fromImage(img.scaled(40,
                                               40,
                                               Qt::IgnoreAspectRatio,
                                               Qt::SmoothTransformation));

    QPainterPath path;
    path.addEllipse(width()/2-20, height()/2-20, 40, 40);
    painter.setClipPath(path);

    painter.drawPixmap(QRect(width()/2-20, height()/2-20, 40, 40), pm);
}
