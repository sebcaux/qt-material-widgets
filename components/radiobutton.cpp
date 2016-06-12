#include "radiobutton.h"
#include <QPainter>
#include <QEvent>
#include "radiobutton_p.h"
#include "lib/rippleoverlay.h"

RadioButtonPrivate::RadioButtonPrivate(RadioButton *q)
    : q_ptr(q),
      checkedIcon(QIcon("../qt-material-widgets/ic_radio_button_checked_black_24px.svg")),
      uncheckedIcon(QIcon("../qt-material-widgets/ic_radio_button_unchecked_black_24px.svg"))
{
}

void RadioButtonPrivate::init()
{
    Q_Q(RadioButton);

    ripple = new RippleOverlay(q->parentWidget());
    iconWidget = new RadioButtonIcon(q);

    QFont f(q->font());
    f.setPointSizeF(11);
    q->setFont(f);
}

RadioButton::RadioButton(QWidget *parent)
    : QRadioButton(parent),
      d_ptr(new RadioButtonPrivate(this))
{
    d_func()->init();

    //QPushButton *b = new QPushButton;
    //b->setParent(this);
    //b->setIcon(d_func()->checkedIcon);
    //b->setIconSize(QSize(12, 12));

    //QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect;
    //effect->setColor(Qt::blue);
    //b->setGraphicsEffect(effect);
}

RadioButton::~RadioButton()
{
}

QSize RadioButton::sizeHint() const
{
    QString s(text());
    if (s.isEmpty())
        return QSize(32, 32);

    QFontMetrics fm = fontMetrics();
    QSize sz = fm.size(Qt::TextShowMnemonic, s);

    return QSize(sz.width() + 44, 32);
}

bool RadioButton::event(QEvent *event)
{
    Q_D(RadioButton);

    switch (event->type())
    {
    case QEvent::Resize:
    case QEvent::Move:
        d->ripple->setGeometry(geometry().adjusted(-8, -8, 8, 8));
        d->iconWidget->setGeometry(geometry());
        break;
    case QEvent::ParentChange:
        QWidget *widget;
        if ((widget = parentWidget())) {
            d->ripple->setParent(widget);
        }
        break;
    default:
        break;
    }
    return QRadioButton::event(event);
}

void RadioButton::mousePressEvent(QMouseEvent *event)
{
    Q_D(RadioButton);

    d->ripple->addRipple(QPoint(24, 24), 24);

    QRadioButton::mousePressEvent(event);
}

void RadioButton::mouseReleaseEvent(QMouseEvent *event)
{
    QRadioButton::mouseReleaseEvent(event);
}

void RadioButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    //Q_D(RadioButton);

    QPainter painter(this);

    //painter.save();
    //QRadioButton::paintEvent(event);
    //painter.restore();

    //painter.drawRect(rect().adjusted(0, 0, -1, -1));

    // Icon

    //d->checkedIcon.paint(&painter, QRect(4, 4, 24, 24), Qt::AlignCenter, QIcon::Normal);

    //d->checkedIcon.pixmap()

    // Label

    painter.drawText(44, 21, text());
}
