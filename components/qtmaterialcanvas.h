#ifndef QTMATERIALCANVAS_H
#define QTMATERIALCANVAS_H

#include "qtmaterialwidgets.h"

#include <QScrollArea>

class QtMaterialCanvasPrivate;

class QTMATERIALWIDGETS_EXPORT QtMaterialCanvas : public QScrollArea
{
    Q_OBJECT

    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)

public:
    explicit QtMaterialCanvas(QWidget *parent = nullptr);
    explicit QtMaterialCanvas(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~QtMaterialCanvas() override;

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

protected:
    const QScopedPointer<QtMaterialCanvasPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialCanvas)
    Q_DECLARE_PRIVATE(QtMaterialCanvas)

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALCANVAS_H
