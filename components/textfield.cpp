#include "textfield.h"
#include <QPainter>
#include <QApplication>
#include "textfield_p.h"
#include "textfield_internal.h"

TextFieldPrivate::TextFieldPrivate(TextField *q)
    : q_ptr(q)
{
    q->setFrame(false);
    q->setTextMargins(0, 1, 0, 1);
}

void TextFieldPrivate::init()
{
    Q_Q(TextField);

    machine = new TextFieldStateMachine(q);

    machine->start();

    QCoreApplication::processEvents();
}

TextField::TextField(QWidget *parent)
    : QLineEdit(parent),
      d_ptr(new TextFieldPrivate(this))
{
    d_func()->init();

    //

    setPlaceholderText("This is a placeholder");

    QPalette p;
    p.setColor(QPalette::Normal, QPalette::Base, p.color(QPalette::Window));
//    p.setColor(QPalette::Normal, QPalette::Text, Qt::blue);
    setPalette(p);
}

TextField::~TextField()
{
}

void TextField::setTextColor(const QColor &color)
{
}

QColor TextField::textColor() const
{
}

void TextField::setBackgroundColor(const QColor &color)
{
}

QColor TextField::backgroundColor() const
{
}

void TextField::setInkColor(const QColor &color)
{
}

QColor TextField::inkColor() const
{
}

void TextField::setUnderlineColor(const QColor &color)
{
}

QColor TextField::underlineColor() const
{
}

void TextField::paintEvent(QPaintEvent *event)
{
    Q_D(TextField);

    QLineEdit::paintEvent(event);

    QPainter painter(this);

//    {
//        painter.drawText(0, height()/2, text());
//    }

    //QBrush bgBrush;
    //bgBrush.setStyle(Qt::SolidPattern);
    //bgBrush.setColor(palette().color(QPalette::Window));
    //painter.fillRect(rect(), bgBrush);

    const int y = height()-1;
    painter.drawLine(0, y, width(), y);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    const qreal progress = d->machine->progress();

    if (progress > 0) {

        painter.setPen(Qt::NoPen);
        painter.setBrush(brush);

        int w = (1-progress)*static_cast<qreal>(width()/2);

        painter.drawRect(w, height()-2, width()-w*2, 2);

    }
}
