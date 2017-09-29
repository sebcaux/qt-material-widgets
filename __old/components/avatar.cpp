#include "avatar.h"
#include "avatar_p.h"
#include <QWidget>
#include <QPainter>
#include <QIcon>
#include "lib/style.h"

AvatarPrivate::AvatarPrivate(Avatar *q)
    : q_ptr(q),
      size(40),
      type(Material::LetterAvatar),
      useThemeColors(true)
{
}

void AvatarPrivate::init()
{
    Q_Q(Avatar);

    QFont font(q->font());
    font.setPointSizeF(16);
    q->setFont(font);

    QSizePolicy policy(QSizePolicy::MinimumExpanding,
                       QSizePolicy::MinimumExpanding);
    q->setSizePolicy(policy);
}

Avatar::Avatar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new AvatarPrivate(this))
{
    d_func()->init();
}

Avatar::Avatar(const QIcon &icon, QWidget *parent)
    : QWidget(parent),
      d_ptr(new AvatarPrivate(this))
{
    d_func()->init();

    setIcon(icon);
}

Avatar::Avatar(const QChar &letter, QWidget *parent)
    : QWidget(parent),
      d_ptr(new AvatarPrivate(this))
{
    d_func()->init();

    setLetter(letter);
}

Avatar::Avatar(const QImage &image, QWidget *parent)
    : QWidget(parent),
      d_ptr(new AvatarPrivate(this))
{
    d_func()->init();

    setImage(image);
}

Avatar::~Avatar()
{
}

void Avatar::setUseThemeColors(bool value)
{
    Q_D(Avatar);

    d->useThemeColors = value;
}

bool Avatar::useThemeColors() const
{
    Q_D(const Avatar);

    return d->useThemeColors;
}

void Avatar::setTextColor(const QColor &color)
{
    Q_D(Avatar);

    d->textColor = color;
    setUseThemeColors(false);
}

QColor Avatar::textColor() const
{
    Q_D(const Avatar);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return Style::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void Avatar::setBackgroundColor(const QColor &color)
{
    Q_D(Avatar);

    d->backgroundColor = color;
    setUseThemeColors(false);
}

QColor Avatar::backgroundColor() const
{
    Q_D(const Avatar);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->backgroundColor;
    }
}

QSize Avatar::sizeHint() const
{
    Q_D(const Avatar);

    return QSize(d->size+2, d->size+2);
}

void Avatar::setSize(int size)
{
    Q_D(Avatar);

    d->size = size;

    if (!d->image.isNull()) {
        d->pixmap = QPixmap::fromImage(d->image.scaled(d->size, d->size,
                                                       Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation));
    }

    QFont f(font());
    f.setPointSizeF(size*16/40);
    setFont(f);

    update();
}

int Avatar::size() const
{
    Q_D(const Avatar);

    return d->size;
}

void Avatar::setLetter(const QChar &letter)
{
    Q_D(Avatar);

    d->letter = letter;
    d->type = Material::LetterAvatar;
}

void Avatar::setImage(const QImage &image)
{
    Q_D(Avatar);

    d->image = image;
    d->type = Material::ImageAvatar;

    d->pixmap = QPixmap::fromImage(image.scaled(d->size, d->size,
                                                Qt::IgnoreAspectRatio,
                                                Qt::SmoothTransformation));
}

void Avatar::setIcon(const QIcon &icon)
{
    Q_D(Avatar);

    d->icon = icon;
    d->type = Material::IconAvatar;
}

void Avatar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(Avatar);

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    QRect r = rect();
    const int hs = d->size/2;

    if (Material::ImageAvatar != d->type)
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(backgroundColor());
        painter.setPen(Qt::NoPen);
        painter.setBrush(brush);
        painter.drawEllipse(r.center(), hs, hs);
    }

    switch (d->type)
    {
    case Material::ImageAvatar:
    {
        QPainterPath path;
        path.addEllipse(width()/2-hs, height()/2-hs, d->size, d->size);
        painter.setClipPath(path);

        painter.drawPixmap(QRect(width()/2-hs, height()/2-hs, d->size, d->size),
                           d->pixmap);
        break;
    }
    case Material::IconAvatar:
    {
        d->icon.paint(&painter,
                      QRect((width()-hs)/2, (height()-hs)/2, hs, hs),
                      Qt::AlignCenter,
                      QIcon::Normal);
        break;
    }
    case Material::LetterAvatar:
    {
        painter.setPen(textColor());
        painter.setBrush(Qt::NoBrush);
        painter.drawText(r.translated(0, -1), Qt::AlignCenter, "A");
        break;
    }
    default:
        break;
    }
}
