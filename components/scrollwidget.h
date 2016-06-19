#ifndef SCROLLWIDGET_H
#define SCROLLWIDGET_H

#include <QScrollBar>

class ScrollBarPrivate;

class ScrollBar : public QScrollBar
{
    Q_OBJECT

public:
    explicit ScrollBar(QWidget *parent = 0);
    ~ScrollBar();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setSliderColor(const QColor &color);
    QColor sliderColor() const;

    void setHideOnMouseOut(bool state);
    bool hideOnMouseOut() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<ScrollBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(ScrollBar)
    Q_DECLARE_PRIVATE(ScrollBar)
};

#endif // SCROLLWIDGET_H
