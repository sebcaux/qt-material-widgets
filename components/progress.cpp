#include "progress.h"
#include <QPainter>
#include "progress_p.h"

ProgressPrivate::ProgressPrivate(Progress *q)
    : q_ptr(q)
{
}

ProgressPrivate::~ProgressPrivate()
{
}

void ProgressPrivate::init()
{
}

Progress::Progress(QWidget *parent)
    : QProgressBar(parent),
      d_ptr(new ProgressPrivate(this))
{
    d_func()->init();
}

Progress::~Progress()
{
}

void Progress::setProgressType(Material::ProgressType type)
{
    Q_D(Progress);

    d->progressType = type;
    update();
}

Material::ProgressType Progress::progressType() const
{
    Q_D(const Progress);

    return d->progressType;
}

void Progress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

//    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    //QRectF r(0, 0, width(), 8);
    //r.moveCenter(rect().center());

    //painter.drawRect(r);

    QPainterPath path;
    path.addRoundedRect(0, height()/2-4, width(), 8, 3, 3);
    painter.setClipPath(path);

    painter.drawRect(0, 0, width(), height());

    brush.setColor(Qt::blue);
    painter.setBrush(brush);

    painter.drawRect(0, 0, width()/2, height());
}
