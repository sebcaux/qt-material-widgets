#ifndef TOGGLE_H
#define TOGGLE_H

#include <QAbstractButton>

class QPropertyAnimation;
class RippleOverlay;
class Toggle;

class Thumb : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal progress WRITE setProgress READ progress NOTIFY progressChanged)

public:
    explicit Thumb(Toggle *parent);
    ~Thumb();

    void setProgress(qreal p);
    inline qreal progress() const { return _progress; }

    inline int offset() const { return _offset; }

signals:
    void clicked();
    void progressChanged(qreal);

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Toggle             *const _toggle;
    QPropertyAnimation *const _animation;
    qreal                     _progress;
    int                       _offset;
};

class Toggle : public QAbstractButton
{
    Q_OBJECT

public:
    explicit Toggle(QWidget *parent = 0);
    ~Toggle();

    QSize sizeHint() const { return QSize(64, 48); }

protected slots:
    void xx();
    void yy();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Thumb         *const _thumb;
    RippleOverlay *const _overlay;
};

#endif // TOGGLE_H
