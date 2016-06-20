#include "dialog_internal.h"
#include <QPainter>
#include "dialog.h"

DialogWindow::DialogWindow(QWidget *parent)
    : QWidget(parent)
{
}

DialogWindow::~DialogWindow()
{
}

void DialogWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);

    painter.drawRect(rect());
}

//DialogProxy::DialogProxy(Dialog *dialog, QWidget *widget)
//    : QWidget(dialog),
//      dialog(dialog),
//      widget(widget)
//{
//}
//
//DialogProxy::~DialogProxy()
//{
//}
//
//void DialogProxy::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event)
//
//    QPainter painter(this);
//
//    //QPen pen;
//    //pen.setWidth(4);
//    //pen.setColor(Qt::red);
//    //painter.setPen(pen);
//
//    //painter.drawRect(rect());
//
//    //
//
//    painter.setOpacity(0.3);
//
//    QPixmap pm = widget->grab(rect());
//    painter.drawPixmap(rect(), pm);
//
//}
//
//DialogWindow::DialogWindow(Dialog *dialog)
//    : QWidget(dialog->parentWidget()),
//      dialog(dialog)
//{
//    setContentsMargins(32, 32, 32, 32);
//
//    qDebug() << dialog->parentWidget();
//}
//
//DialogWindow::~DialogWindow()
//{
//}
//
//void DialogWindow::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event)
//
//    QPainter painter(this);
//
//    QPen pen;
//    pen.setColor(Qt::red);
//    pen.setWidth(1);
//    painter.setPen(pen);
//    painter.drawRect(rect().adjusted(0, 0, -1, -1));
//
////    QLinearGradient tl(QPointF(0, 0), QPointF(32, 32));
////    tl.setColorAt(0, QColor(0, 0, 0, 0));
////    tl.setColorAt(1, QColor(0, 0, 0));
//
////    QColor shadow(0, 0, 0, 240);
////
////    QRadialGradient tl(rect().center(), 130);
////    tl.setColorAt(0, shadow);
////    tl.setColorAt(0.5, QColor(0, 0, 0));
////    tl.setColorAt(1, QColor(0, 0, 0, 0));
////
////    painter.setBrush(QBrush(tl));
////    painter.setPen(Qt::NoPen);
////    painter.drawRect(rect().adjusted(32, 32, -32, -32));
//
//    /*
//    QColor shadow(0, 0, 0, 240);
//
//    const int sz = 48;
//
//    QLinearGradient top(QPointF(0, 0), QPointF(0, sz));
//    top.setColorAt(0, QColor(0, 0, 0, 0));
//    top.setColorAt(1, shadow);
//
//    painter.setBrush(QBrush(top));
//    painter.setPen(Qt::NoPen);
//    painter.drawRect(sz, 0, width()-sz*2, sz);
//
//    QLinearGradient left(QPointF(0, 0), QPointF(sz, 0));
//    left.setColorAt(0, QColor(0, 0, 0, 0));
//    left.setColorAt(1, shadow);
//
//    painter.setBrush(QBrush(left));
//    painter.drawRect(0, sz, sz, height()-sz*2);
//
//    QLinearGradient right(QPointF(width()-sz, 0), QPointF(width(), 0));
//    right.setColorAt(0, shadow);
//    right.setColorAt(1, QColor(0, 0, 0, 0));
//
//    painter.setBrush(QBrush(right));
//    painter.drawRect(width()-sz, sz, sz, height()-sz*2);
//
//    QLinearGradient bottom(QPointF(0, height()-sz), QPointF(0, height()));
//    bottom.setColorAt(0, shadow);
//    bottom.setColorAt(1, QColor(0, 0, 0, 0));
//
//    painter.setBrush(QBrush(bottom));
//    painter.setPen(Qt::NoPen);
//    painter.drawRect(sz, height()-sz, width()-sz*2, sz);
//
//    QRadialGradient tl(QPointF(sz, sz), sz);
//    tl.setColorAt(0, shadow);
//    tl.setColorAt(1, QColor(0, 0, 0, 0));
//
//    painter.setBrush(QBrush(tl));
//    painter.drawRect(0, 0, sz, sz);
//
//    QRadialGradient tr(QPointF(width()-sz, sz), sz);
//    tr.setColorAt(0, shadow);
//    tr.setColorAt(1, QColor(0, 0, 0, 0));
//
//    painter.setBrush(QBrush(tr));
//    painter.drawRect(width()-sz, 0, sz, sz);
//
//    QRadialGradient br(QPointF(width()-sz, height()-sz), sz);
//    br.setColorAt(0, shadow);
//    br.setColorAt(1, QColor(0, 0, 0, 0));
//
//    painter.setBrush(QBrush(br));
//    painter.drawRect(width()-sz, height()-sz, sz, sz);
//
//    QRadialGradient bl(QPointF(sz, height()-sz), sz);
//    bl.setColorAt(0, shadow);
//    bl.setColorAt(1, QColor(0, 0, 0, 0));
//
//    painter.setBrush(QBrush(bl));
//    painter.drawRect(0, height()-sz, sz, sz);
//    */
//
//    //
//
//    QBrush brush;
//    brush.setStyle(Qt::SolidPattern);
//    brush.setColor(Qt::white);
//    painter.setPen(Qt::NoPen);
//    //painter.setOpacity(0.5);
//    painter.setBrush(brush);
//
//    //QRectF r(0, 0, 200, 200);
//    //r.moveCenter(rect().center());
//
//    painter.drawRect(rect().adjusted(32, 32, -32, -32));
//
//    {
//        QWidget *w = new QWidget;
//
//        QVBoxLayout *layout = new QVBoxLayout;
//        w->setLayout(layout);
//
//        QPushButton *button = new QPushButton;
//        button->setText("Hello test!");
//        layout->addWidget(button);
//
//        //QPixmap pm = w->grab(rect().adjusted(0, 0, -64, -64));
//
//        //QPixmap pm = dialog->dialogWidget()->grab(rect().adjusted(0, 0, -64, -64));
//
//        //painter.drawPixmap(rect().adjusted(32, 32, -32, -32), pm);
//
//        painter.drawRect(rect());
//    }
//
//
//    //brush.setColor(Qt::black);
//    //painter.setBrush(brush);
//    //painter.setOpacity(0.8);
//
//    //painter.drawRect(rect().adjusted(32, 32, -32, -32));
//}
//
//DialogShadow::DialogShadow(QWidget *dialog)
//    : QWidget(dialog)
//{
//}
//
//DialogShadow::~DialogShadow()
//{
//}
//
//void DialogShadow::setWindow(DialogWindow *window)
//{
//    this->window = window;
//    window->installEventFilter(this);
//}
//
//void DialogShadow::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event)
//
//    QPainter painter(this);
//
////    QBrush brush;
////    brush.setStyle(Qt::SolidPattern);
////    brush.setColor(Qt::black);
////    painter.setBrush(brush);
////    painter.setOpacity(1);
////
////    painter.drawRect(rect());
//}
//
//bool DialogShadow::eventFilter(QObject *obj, QEvent *event)
//{
//    QEvent::Type type = event->type();
//
//    if (QEvent::Move == type || QEvent::Resize == type)
//    {
//        QWidget *widget;
//        if ((widget = static_cast<QWidget *>(obj))) {
//            setGeometry(widget->geometry());
//        }
//    }
//    return QWidget::eventFilter(obj, event);
//}
//
