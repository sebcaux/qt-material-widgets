#ifndef TRANSPARENCYPROXY_INTERNAL_H
#define TRANSPARENCYPROXY_INTERNAL_H

#include <QWidget>

class ProxyWidget : public QWidget
{
    Q_OBJECT

public:
    ProxyWidget(QWidget *widget, QWidget *parent = 0);
    ~ProxyWidget();

    inline void setOpacity(qreal opacity) { _opacity = opacity; update(); }
    inline qreal opacity() const { return _opacity; }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(ProxyWidget)

    QWidget *const _widget;
    qreal          _opacity;
};

#endif // TRANSPARENCYPROXY_INTERNAL_H
