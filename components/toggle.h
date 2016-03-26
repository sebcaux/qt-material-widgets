#ifndef TOGGLE_H
#define TOGGLE_H

#include <QAbstractButton>

class RippleOverlay;

class Thumb : public QWidget
{
    Q_OBJECT

public:
    explicit Thumb(QWidget *parent = 0);
    ~Thumb();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};

class Toggle : public QAbstractButton
{
    Q_OBJECT

public:
    explicit Toggle(QWidget *parent = 0);
    ~Toggle();

    QSize sizeHint() const { return QSize(32, 32); }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    RippleOverlay *const _overlay;
    Thumb         *const _thumb;
};

#endif // TOGGLE_H
