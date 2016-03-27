#ifndef TOGGLE_H
#define TOGGLE_H

#include <QAbstractButton>

class QPropertyAnimation;
class RippleOverlay;
class Toggle;

class Thumb : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal progress WRITE setProgress READ progress)

public:
    explicit Thumb(Toggle *parent);
    ~Thumb();

    inline void setProgress(qreal p) { _progress = p; }
    inline qreal progress() const { return _progress; }

signals:
    void clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Toggle             *const _toggle;
    QPropertyAnimation *const _animation;
    qreal _progress;
};

class Toggle : public QAbstractButton
{
    Q_OBJECT

public:
    explicit Toggle(QWidget *parent = 0);
    ~Toggle();

    QSize sizeHint() const { return QSize(132, 64); }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    RippleOverlay *const _overlay;
    Thumb         *const _thumb;
};

#endif // TOGGLE_H
