#include "transparencyproxy.h"
#include "transparencyproxy_p.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include "transparencyproxy_internal.h"

TransparencyProxyPrivate::TransparencyProxyPrivate(TransparencyProxy *q)
    : q_ptr(q),
      widget(0),
      proxy(0)
{
}

TransparencyProxyPrivate::~TransparencyProxyPrivate()
{
}

void TransparencyProxyPrivate::init()
{
}

TransparencyProxy::TransparencyProxy()
    : QStackedLayout(),
      d_ptr(new TransparencyProxyPrivate(this))
{
    d_func()->init();
}

TransparencyProxy::~TransparencyProxy()
{
}

void TransparencyProxy::setWidget(QWidget *widget)
{
    Q_D(TransparencyProxy);

    if(d->widget) {
        removeWidget(d->widget);
        delete d->widget;
    }
    d->widget = widget;

    if (d->proxy) {
        removeWidget(d->proxy);
        delete d->proxy;
    }
    d->proxy = new ProxyWidget(widget);

    addWidget(widget);
    addWidget(d->proxy);
}

void TransparencyProxy::setOpaque()
{
    Q_D(TransparencyProxy);

    if (!d->proxy) {
        return;
    }

    d->proxy->setOpacity(1);
    setCurrentIndex(0);

    emit opacityChanged();
}

void TransparencyProxy::setOpacity(qreal opacity)
{
    Q_D(TransparencyProxy);

    if (!d->proxy) {
        return;
    }

    if (1 == opacity) {
        return setOpaque();
    }

    d->proxy->setOpacity(opacity);
    setCurrentIndex(1);

    emit opacityChanged();
}

qreal TransparencyProxy::opacity() const
{
    Q_D(const TransparencyProxy);

    return d->proxy->opacity();
}
