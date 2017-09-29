#ifndef SIZEPROXYWIDGET_H
#define SIZEPROXYWIDGET_H

#include <QWidget>

class SizeProxyWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal canvasXScale WRITE setCanvasXScale READ canvasXScale)
    Q_PROPERTY(qreal canvasYScale WRITE setCanvasYScale READ canvasYScale)
    Q_PROPERTY(qreal xScale WRITE setXScale READ xScale)
    Q_PROPERTY(qreal yScale WRITE setYScale READ yScale)
    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
    SizeProxyWidget(QWidget *source, QWidget *parent = 0);
    ~SizeProxyWidget();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    inline QRect sourceGeometry() const;

    void setCanvasXScale(qreal s);
    inline qreal canvasXScale() const;

    void setCanvasYScale(qreal s);
    inline qreal canvasYScale() const;

    void setXScale(qreal s);
    inline qreal xScale() const;

    void setYScale(qreal s);
    inline qreal yScale() const;

    void setOpacity(qreal opacity);
    inline qreal opacity() const;

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    //bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(SizeProxyWidget)

    void banan();

    QWidget *const m_sourceWidget;
    QPixmap        m_pixmap;
    qreal          m_canvasSx;
    qreal          m_canvasSy;
    qreal          m_sx;
    qreal          m_sy;
    qreal          m_opacity;
};

inline QRect SizeProxyWidget::sourceGeometry() const
{
    return m_sourceWidget->geometry();
}

inline qreal SizeProxyWidget::canvasXScale() const
{
    return m_canvasSx;
}

inline qreal SizeProxyWidget::canvasYScale() const
{
    return m_canvasSy;
}

inline qreal SizeProxyWidget::xScale() const
{
    return m_sx;
}

inline qreal SizeProxyWidget::yScale() const
{
    return m_sy;
}

inline qreal SizeProxyWidget::opacity() const
{
    return m_opacity;
}

#endif // SIZEPROXYWIDGET_H
