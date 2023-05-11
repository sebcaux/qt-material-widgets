#ifndef QTMATERIALWIDGET_H
#define QTMATERIALWIDGET_H

#include <QWidget>

class QtMaterialWidgetPrivate;

class QtMaterialWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialWidget(QWidget *parent = nullptr);
    ~QtMaterialWidget() override;

    bool useThemeColors() const;
    void setUseThemeColors(bool value);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

protected:
    const QScopedPointer<QtMaterialWidgetPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialWidget)
    Q_DECLARE_PRIVATE(QtMaterialWidget)

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALWIDGET_H
