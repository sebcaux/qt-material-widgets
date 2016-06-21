#ifndef TRANSPARENCYPROXY_P_H
#define TRANSPARENCYPROXY_P_H

#include <QObject>

class TransparencyProxy;
class ProxyWidget;

class TransparencyProxyPrivate
{
    Q_DISABLE_COPY(TransparencyProxyPrivate)
    Q_DECLARE_PUBLIC(TransparencyProxy)

public:
    TransparencyProxyPrivate(TransparencyProxy *q);
    ~TransparencyProxyPrivate();

    void init();

    TransparencyProxy *const q_ptr;
    QWidget           *widget;
    ProxyWidget       *proxy;
};

#endif // TRANSPARENCYPROXY_P_H
