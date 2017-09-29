#ifndef SIZEPROXY_H
#define SIZEPROXY_H

#include <QStackedLayout>
#include <QWidget>

class SizeProxy;

class ProxyWidget2 : public QWidget
{
    Q_OBJECT

public:
    explicit ProxyWidget2(QWidget *source, QWidget *parent = 0);
    ~ProxyWidget2();

//    QSize sizeHint() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(ProxyWidget2)

    friend class SizeProxy;

    QWidget *const m_sourceWidget;
    qreal          m_sx;
    qreal          m_sy;
    bool           m_scaled;
};

class SizeProxy : public QStackedLayout
{
    Q_OBJECT

    Q_PROPERTY(qreal xScale WRITE setXScale READ xScale)
    Q_PROPERTY(qreal yScale WRITE setYScale READ yScale)

public:
    explicit SizeProxy(QWidget *widget);
    ~SizeProxy();

    void setGeometry(const QRect &geometry);

    void setScale(qreal sx, qreal sy);
    void getScale(qreal *sx, qreal *sy);

    void setXScale(qreal s);
    qreal xScale() const;

    void setYScale(qreal s);
    qreal yScale() const;

private:
    Q_DISABLE_COPY(SizeProxy)

    ProxyWidget2 *const m_proxy;
};

#endif // SIZEPROXY_H
