#ifndef QTMATERIALCANVAS_H
#define QTMATERIALCANVAS_H

#include <QScrollArea>

class QtMaterialCanvasPrivate;

class QtMaterialCanvas : public QScrollArea
{
    Q_OBJECT

public:
    explicit QtMaterialCanvas(QWidget *parent = nullptr);
    ~QtMaterialCanvas() override;

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
