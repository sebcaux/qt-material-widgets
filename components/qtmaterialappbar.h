#ifndef QTMATERIALAPPBAR_H
#define QTMATERIALAPPBAR_H

#include <QWidget>

class QtMaterialAppBarPrivate;

class QtMaterialAppBar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    explicit QtMaterialAppBar(QWidget *parent = nullptr);
    ~QtMaterialAppBar() override;

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor foregroundColor() const;
    void setForegroundColor(const QColor &color);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

protected:
    const QScopedPointer<QtMaterialAppBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialAppBar)
    Q_DECLARE_PRIVATE(QtMaterialAppBar)

    // QWidget interface
public:
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALAPPBAR_H
