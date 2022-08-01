#ifndef QTMATERIALSCROLLBAR_H
#define QTMATERIALSCROLLBAR_H

#include <QScrollBar>

class QtMaterialScrollBarPrivate;

class QtMaterialScrollBar : public QScrollBar
{
    Q_OBJECT

    Q_PROPERTY(QColor canvasColor WRITE setCanvasColor READ canvasColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor sliderColor WRITE setSliderColor READ sliderColor)

public:
    explicit QtMaterialScrollBar(QWidget *parent = nullptr);
    ~QtMaterialScrollBar() override;

    QSize sizeHint() const override;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setCanvasColor(const QColor &color);
    QColor canvasColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setSliderColor(const QColor &color);
    QColor sliderColor() const;

    void setHideOnMouseOut(bool value);
    bool hideOnMouseOut() const;

protected:
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<QtMaterialScrollBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialScrollBar)
    Q_DECLARE_PRIVATE(QtMaterialScrollBar)

    // QAbstractSlider interface
protected:
    void sliderChange(SliderChange change) override;
};

#endif  // QTMATERIALSCROLLBAR_H
