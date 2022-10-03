#ifndef QTMATERIALSWITCH_INTERNAL_H
#define QTMATERIALSWITCH_INTERNAL_H

#include "lib/qtmaterialrippleoverlay.h"

#include <QWidget>

class QtMaterialSwitch;
class QtMaterialSwitchThumb;
class QtMaterialSwitchTrack;

class QtMaterialSwitchRippleOverlay : public QtMaterialRippleOverlay
{
    Q_OBJECT

public:
    QtMaterialSwitchRippleOverlay(QtMaterialSwitchThumb *thumb, QtMaterialSwitchTrack *track, QtMaterialSwitch *parent);
    ~QtMaterialSwitchRippleOverlay() override;

protected slots:
    void addSwitchRipple();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    QRect overlayGeometry() const override;

private:
    Q_DISABLE_COPY(QtMaterialSwitchRippleOverlay)

    QtMaterialSwitch *const m_switch;
    QtMaterialSwitchThumb *const m_thumb;
    QtMaterialSwitchTrack *const m_track;
};

class QtMaterialSwitchThumb : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal shift WRITE setShift READ shift)
    Q_PROPERTY(QColor thumbColor WRITE setThumbColor READ thumbColor)

public:
    QtMaterialSwitchThumb(QtMaterialSwitch *parent);
    ~QtMaterialSwitchThumb() override;

    void setShift(qreal shift);
    inline qreal shift() const;

    inline qreal offset() const;

    inline void setThumbColor(const QColor &color);
    inline QColor thumbColor() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(QtMaterialSwitchThumb)

    void updateOffset();

    QtMaterialSwitch *const m_switch;
    QColor m_thumbColor;
    qreal m_shift;
    qreal m_offset;
};

inline qreal QtMaterialSwitchThumb::shift() const
{
    return m_shift;
}

inline qreal QtMaterialSwitchThumb::offset() const
{
    return m_offset;
}

inline void QtMaterialSwitchThumb::setThumbColor(const QColor &color)
{
    m_thumbColor = color;
    update();
}

inline QColor QtMaterialSwitchThumb::thumbColor() const
{
    return m_thumbColor;
}

class QtMaterialSwitchTrack : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)

public:
    QtMaterialSwitchTrack(QtMaterialSwitch *parent);
    ~QtMaterialSwitchTrack() override;

    void setTrackColor(const QColor &color);
    inline QColor trackColor() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(QtMaterialSwitchTrack)

    QtMaterialSwitch *const m_switch;
    QColor m_trackColor;
};

inline QColor QtMaterialSwitchTrack::trackColor() const
{
    return m_trackColor;
}

#endif  // QTMATERIALSWITCH_INTERNAL_H
