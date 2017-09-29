#ifndef TOGGLE_H
#define TOGGLE_H

#include <QAbstractButton>

class TogglePrivate;
class ToggleTrack;
class ToggleThumb;

class Toggle : public QAbstractButton
{
    Q_OBJECT

    Q_PROPERTY(QColor disabledColor WRITE setDisabledColor READ disabledColor)
    Q_PROPERTY(QColor activeColor WRITE setActiveColor READ activeColor)
    Q_PROPERTY(QColor inactiveColor WRITE setInactiveColor READ inactiveColor)
    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)

public:
    explicit Toggle(QWidget *parent = 0);
    ~Toggle();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

    void setActiveColor(const QColor &color);
    QColor activeColor() const;

    void setInactiveColor(const QColor &color);
    QColor inactiveColor() const;

    void setTrackColor(const QColor &color);
    QColor trackColor() const;

    QSize sizeHint() const;

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    void updateOverlayGeometry();

protected slots:
    void addRipple();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<TogglePrivate> d_ptr;

private:
    Q_DISABLE_COPY(Toggle)
    Q_DECLARE_PRIVATE(Toggle)

    friend class ToggleTrack;
    friend class ToggleThumb;
};

#endif // TOGGLE_H
