#include "snackbar.h"
#include "snackbar_p.h"
#include <QPainter>
#include <QEvent>
#include <QDebug>
#include <QFontDatabase>
#include "snackbar_internal.h"

SnackbarPrivate::SnackbarPrivate(Snackbar *q)
    : q_ptr(q),
      machine(0),
      duration(3000),
      boxWidth(300)
{
}

SnackbarPrivate::~SnackbarPrivate()
{
}

void SnackbarPrivate::init()
{
    Q_Q(Snackbar);

    machine = new SnackbarStateMachine(q);

    q->setAttribute(Qt::WA_TransparentForMouseEvents);

    QFontDatabase db;
    QFont font(db.font("Roboto", "Medium", 10));
    font.setCapitalization(QFont::AllUppercase);
    q->setFont(font);

    backgroundColor = QColor(0, 0, 0, 220);
    textColor = Qt::white;

    if (q->parentWidget()) {
        q->parentWidget()->installEventFilter(q);
    }

    machine->start();
}

Snackbar::Snackbar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new SnackbarPrivate(this))
{
    d_func()->init();
}

Snackbar::~Snackbar()
{
}

void Snackbar::setAutoHideDuration(int duration)
{
    Q_D(Snackbar);

    d->duration = duration;
}

int Snackbar::autoHideDuration() const
{
    Q_D(const Snackbar);

    return d->duration;
}

void Snackbar::setBackgroundColor(const QColor &color)
{
    Q_D(Snackbar);

    d->backgroundColor = color;
}

QColor Snackbar::backgroundColor() const
{
    Q_D(const Snackbar);

    return d->backgroundColor;
}

void Snackbar::setTextColor(const QColor &color)
{
    Q_D(Snackbar);

    d->textColor = color;
}

QColor Snackbar::textColor() const
{
    Q_D(const Snackbar);

    return d->textColor;
}

void Snackbar::setFontSize(qreal size)
{
    QFont f(font());
    f.setPointSizeF(size);
    setFont(f);

    update();
}

qreal Snackbar::fontSize() const
{
    return font().pointSizeF();
}

void Snackbar::setBoxWidth(int width)
{
    Q_D(Snackbar);

    d->boxWidth = width;
    update();
}

int Snackbar::boxWidth() const
{
    Q_D(const Snackbar);

    return d->boxWidth;
}

void Snackbar::addMessage(const QString &message, bool instant)
{
    Q_D(Snackbar);

    if (instant && !d->messages.isEmpty()) {
        d->messages.insert(1, message);
    } else {
        d->messages.push_back(message);
    }

    if (instant) {
        emit d->machine->hideSnackbar();
    } else {
        emit d->machine->showSnackbar();
    }
}

bool Snackbar::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::ParentChange:
    {
        if (!parent())
            break;

        parent()->installEventFilter(this);

        QWidget *widget;
        if ((widget = parentWidget())) {
            setGeometry(widget->rect());
        }
        break;
    }
    case QEvent::ParentAboutToChange:
    {
        if (!parent())
            break;

        parent()->removeEventFilter(this);
        break;
    }
    default:
        break;
    }
    return QWidget::event(event);
}

bool Snackbar::eventFilter(QObject *obj, QEvent *event)
{
    QEvent::Type type = event->type();

    if (QEvent::Move == type || QEvent::Resize == type)
    {
        QWidget *widget;
        if ((widget = parentWidget())) {
            setGeometry(widget->rect());
        }
    }
    return QWidget::eventFilter(obj, event);
}

void Snackbar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(Snackbar);

    if (d->messages.isEmpty()) {
        return;
    }

    QString message = d->messages.first();

    QPainter painter(this);

    QRectF r = painter.boundingRect(QRect((width()-d->boxWidth)/2, 0, d->boxWidth, 40),
                                    Qt::AlignCenter | Qt::TextWordWrap,
                                    message);

    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(d->backgroundColor);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    QRectF s((width()-d->boxWidth)/2, 0, d->boxWidth, 40);

    s = r.united(s);

    const int yOffs = height()-s.height()-s.top()
                    + static_cast<qreal>(s.height()+20)*d->machine->offset();

    s.translate(0, yOffs);
    r.translate(0, yOffs-5);

    painter.drawRoundedRect(s.adjusted(-10, -10, 10, 10), 3, 3);
    painter.setPen(d->textColor);
    painter.drawText(r, Qt::AlignCenter | Qt::TextWordWrap, message, &r);
}

void Snackbar::dequeue()
{
    Q_D(Snackbar);

    if (d->messages.isEmpty()) {
        return;
    }

    d->messages.removeFirst();

    if (!d->messages.isEmpty()) {
        emit d->machine->showNextSnackbar();
    } else {
        emit d->machine->waitForSnackbar();
    }
}
