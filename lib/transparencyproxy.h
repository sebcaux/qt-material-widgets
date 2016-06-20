#ifndef TRANSPARENCYPROXY_H
#define TRANSPARENCYPROXY_H

#include <QStackedLayout>

class QWidget;
class TransparencyProxyPrivate;

class TransparencyProxy : public QStackedLayout
{
    Q_OBJECT

public:
    TransparencyProxy();
    ~TransparencyProxy();

    void setWidget(QWidget *widget);

    void setOpaque();
    void setOpacity(qreal opacity);

protected:
    const QScopedPointer<TransparencyProxyPrivate> d_ptr;

private:
    Q_DISABLE_COPY(TransparencyProxy)
    Q_DECLARE_PRIVATE(TransparencyProxy)
};

#endif // TRANSPARENCYPROXY_H
