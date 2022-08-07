#ifndef QTMATERIALSLIDELAYOUT_H
#define QTMATERIALSLIDELAYOUT_H

#include <QEasingCurve>
#include <QStackedLayout>

class QtMaterialSlideLayoutPrivate;

class QtMaterialSlideLayout : public QStackedLayout
{
    Q_OBJECT

    Q_PROPERTY(uint animationDuration WRITE setAnimationDuration READ animationDuration)
    Q_PROPERTY(QEasingCurve::Type animationType WRITE setAnimationType READ animationType)
    Q_PROPERTY(Qt::Orientation orientation WRITE setOrientation READ orientation)

public:
    explicit QtMaterialSlideLayout(QWidget *parent = nullptr);
    explicit QtMaterialSlideLayout(QLayout *parentLayout);
    ~QtMaterialSlideLayout() override;

    uint animationDuration() const;
    void setAnimationDuration(uint animationDuration);

    QEasingCurve::Type animationType() const;
    void setAnimationType(const QEasingCurve::Type animationType);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

protected:
    const QScopedPointer<QtMaterialSlideLayoutPrivate> d_ptr;

public slots:
    void slideToIndex(int index);
    void slideToWidget(QWidget *widget);

private:
    Q_DISABLE_COPY(QtMaterialSlideLayout)
    Q_DECLARE_PRIVATE(QtMaterialSlideLayout)

    // QLayoutItem interface
public:
    void setGeometry(const QRect &rect) override;
};

#endif  // QTMATERIALSLIDELAYOUT_H
