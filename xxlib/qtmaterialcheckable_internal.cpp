#include "xxlib/qtmaterialcheckable_internal.h"
#include <QPainter>

QtMaterialCheckableIcon::QtMaterialCheckableIcon(const QIcon &icon, QWidget *parent)
    : QWidget(parent),
      m_color(Qt::black),
      m_icon(icon),
      m_iconSize(24),
      m_opacity(1.0)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

QtMaterialCheckableIcon::~QtMaterialCheckableIcon()
{
}

QSize QtMaterialCheckableIcon::sizeHint() const
{
    return QSize(m_iconSize, m_iconSize);
}

void QtMaterialCheckableIcon::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawRect(rect());

    painter.setOpacity(m_opacity);
}
