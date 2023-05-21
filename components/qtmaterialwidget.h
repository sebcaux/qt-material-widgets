#ifndef QTMATERIALWIDGET_H
#define QTMATERIALWIDGET_H

#include "qtmaterialwidgets.h"

#include <QWidget>

class QtMaterialWidgetPrivate;

class QTMATERIALWIDGETS_EXPORT QtMaterialWidget : public QWidget
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
