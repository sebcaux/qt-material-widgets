#ifndef TOGGLE_H
#define TOGGLE_H

#endif // TOGGLE_H

//#ifndef TOGGLE_H
//#define TOGGLE_H
//
//#include <QAbstractButton>
//
//class QPropertyAnimation;
//class RippleOverlay;
//class Toggle;
//
//class Thumb : public QWidget
//{
//    Q_OBJECT
//
//    Q_PROPERTY(qreal progress WRITE setProgress READ progress)
//
//public:
//    explicit Thumb(Toggle *parent);
//    ~Thumb();
//
//    void setProgress(qreal progress);
//    inline qreal progress() const { return _progress; }
//
//    inline void setOffset(int offset) { _offset = offset; }
//    inline int offset() const { return _offset; }
//
//signals:
//    void clicked();
//
//protected:
//    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
//    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
//
//private:
//    Toggle             *const _toggle;
//    QPropertyAnimation *const _animation;
//    qreal                     _progress;
//    int                       _offset;
//};
//
//class Toggle : public QAbstractButton
//{
//    Q_OBJECT
//
//    friend class Thumb;
//
//    void updateOverlayGeometry();
//
//public:
//    explicit Toggle(QWidget *parent = 0);
//    ~Toggle();
//
//    QSize sizeHint() const;
//
//    inline Qt::Orientation orientation() const { return _orientation; }
//    void setOrientation(Qt::Orientation orientation);
//
//protected slots:
//    void addRipple();
//
//protected:
//    bool event(QEvent *event) Q_DECL_OVERRIDE;
//    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
//
//private:
//    Thumb         *const _thumb;
//    RippleOverlay *const _overlay;
//    Qt::Orientation      _orientation;
//};
//
//#endif // TOGGLE_H
//
