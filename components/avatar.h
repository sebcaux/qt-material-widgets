#ifndef AVATAR_H
#define AVATAR_H

#include <QWidget>

class AvatarPrivate;

class Avatar : public QWidget
{
    Q_OBJECT

    enum AvatarType {
        ImageAvatar,
        IconAvatar,
        LetterAvatar
    };

public:
    explicit Avatar(QWidget *parent = 0);
    ~Avatar();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<AvatarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Avatar)
    Q_DECLARE_PRIVATE(Avatar)
};

#endif // AVATAR_H
