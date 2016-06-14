#include "textfield.h"
#include "textfield_p.h"

TextFieldPrivate::TextFieldPrivate(TextField *q)
    : q_ptr(q)
{
}

void TextFieldPrivate::init()
{
}

TextField::TextField(QWidget *parent)
    : QLineEdit(parent),
      d_ptr(new TextFieldPrivate(this))
{
    d_func()->init();
}

TextField::~TextField()
{
}

//#include <QPropertyAnimation>
//#include <QWidget>
//#include <QPainter>
//#include <QDebug>
//#include "textfield.h"
//#include "lib/style.h"
//
//TextField::TextField(QWidget *parent)
//    : QLineEdit(parent),
//      _animation(new QPropertyAnimation(this)),
//      _progress(1)
//{
//    setStyle(&Style::instance());
//
//    _animation->setPropertyName("progress");
//    _animation->setTargetObject(this);
//    _animation->setEasingCurve(QEasingCurve::InCubic);
//    _animation->setDuration(350);
//    _animation->setStartValue(1);
//    _animation->setEndValue(0);
//}
//
//TextField::~TextField()
//{
//}
//
//void TextField::setProgress(qreal progress)
//{
//    if (_progress == progress)
//        return;
//    _progress = progress;
//
//    emit progressChanged(progress);
//    update();
//}
//
//void TextField::focusInEvent(QFocusEvent *event)
//{
//    _animation->setDirection(QAbstractAnimation::Forward);
//    _animation->start();
//
//    QLineEdit::focusInEvent(event);
//}
//
//void TextField::focusOutEvent(QFocusEvent *event)
//{
//    _animation->setDirection(QAbstractAnimation::Backward);
//    _animation->start();
//
//    QLineEdit::focusOutEvent(event);
//}
//
//void TextField::mousePressEvent(QMouseEvent *event)
//{
//    QLineEdit::mousePressEvent(event);
//}
//
//void TextField::mouseReleaseEvent(QMouseEvent *event)
//{
//    QLineEdit::mouseReleaseEvent(event);
//}
//
//void TextField::paintEvent(QPaintEvent *event)
//{
//    QLineEdit::paintEvent(event);
//
//    QPainter painter(this);
//
//    QBrush brush;
//    brush.setStyle(Qt::SolidPattern);
//
//    if (!qFuzzyCompare(1, _progress)) {
//
//        painter.setPen(Qt::NoPen);
//        painter.setBrush(brush);
//
//        int w = _progress*static_cast<qreal>(width()/2);
//
//        painter.drawRect(w, height()-2, width()-w*2, 2);
//    }
//}
//
