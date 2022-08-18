#ifndef QTMATERIALSCROLLBAR_H
#define QTMATERIALSCROLLBAR_H

#include <QScrollBar>

class QtMaterialScrollBarPrivate;

class QtMaterialScrollBar : public QScrollBar
{
    Q_OBJECT

    Q_PROPERTY(bool hideOnMouseOut READ hideOnMouseOut WRITE setHideOnMouseOut)
    Q_PROPERTY(QColor canvasColor READ canvasColor WRITE setCanvasColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor sliderColor READ sliderColor WRITE setSliderColor)

public:
    explicit QtMaterialScrollBar(QWidget *parent = nullptr);
    explicit QtMaterialScrollBar(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~QtMaterialScrollBar() override;

    bool hideOnMouseOut() const;
    void setHideOnMouseOut(bool value);

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor canvasColor() const;
    void setCanvasColor(const QColor &color);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);
    QColor sliderColor() const;
    void setSliderColor(const QColor &color);

protected:
    const QScopedPointer<QtMaterialScrollBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialScrollBar)
    Q_DECLARE_PRIVATE(QtMaterialScrollBar)

    // QWidget interface
public:
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

    // QAbstractSlider interface
protected:
    void sliderChange(SliderChange change) override;
};

#endif  // QTMATERIALSCROLLBAR_H
