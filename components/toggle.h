#ifndef TOGGLE_H
#define TOGGLE_H

#include <QAbstractButton>

class RippleOverlay;

class Toggle : public QAbstractButton
{
    Q_OBJECT

public:
    explicit Toggle(QWidget *parent = 0);
    ~Toggle();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    RippleOverlay *const _overlay;
};

#endif // TOGGLE_H
