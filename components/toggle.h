#ifndef TOGGLE_H
#define TOGGLE_H

#include <QAbstractButton>

class TogglePrivate;

class Toggle : public QAbstractButton
{
    Q_OBJECT

public:
    explicit Toggle(QWidget *parent = 0);
    ~Toggle();

    QSize sizeHint() const;

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation) Q_DECL_OVERRIDE;

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
};

#endif // TOGGLE_H
