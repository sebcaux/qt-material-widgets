#ifndef QTMATERIALTOGGLE_H
#define QTMATERIALTOGGLE_H

#include <QAbstractButton>

class QtMaterialTogglePrivate;

class QtMaterialToggle : public QAbstractButton
{
    Q_OBJECT

    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
    Q_PROPERTY(QColor disabledColor READ disabledColor WRITE setDisabledColor)
    Q_PROPERTY(QColor activeColor READ activeColor WRITE setActiveColor)
    Q_PROPERTY(QColor inactiveColor READ inactiveColor WRITE setInactiveColor)
    Q_PROPERTY(QColor trackColor READ trackColor WRITE setTrackColor)

public:
    explicit QtMaterialToggle(QWidget *parent = nullptr);
    explicit QtMaterialToggle(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~QtMaterialToggle() override;

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor disabledColor() const;
    void setDisabledColor(const QColor &color);
    QColor activeColor() const;
    void setActiveColor(const QColor &color);
    QColor inactiveColor() const;
    void setInactiveColor(const QColor &color);
    QColor trackColor() const;
    void setTrackColor(const QColor &color);

protected:
    const QScopedPointer<QtMaterialTogglePrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialToggle)
    Q_DECLARE_PRIVATE(QtMaterialToggle)

    // QWidget interface
public:
    QSize sizeHint() const override;

protected:
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALTOGGLE_H
