#ifndef QTMATERIALBADGE_H
#define QTMATERIALBADGE_H

#include "lib/qtmaterialoverlaywidget.h"

class QtMaterialBadgePrivate;

class QtMaterialBadge : public QtMaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QPointF relativePosition WRITE setRelativePosition READ relativePosition)

public:
    explicit QtMaterialBadge(QWidget *parent = nullptr);
    explicit QtMaterialBadge(const QIcon &icon, QWidget *parent = nullptr);
    explicit QtMaterialBadge(const QString &text, QWidget *parent = nullptr);
    ~QtMaterialBadge() override;

    const QString &text() const;
    void setText(const QString &text);

    const QIcon &icon() const;
    void setIcon(const QIcon &icon);

    const QPointF &relativePosition() const;
    void setRelativePosition(const QPointF &pos);
    void setRelativePosition(qreal x, qreal y);

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor textColor() const;
    void setTextColor(const QColor &color);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

protected:
    const QScopedPointer<QtMaterialBadgePrivate> d_ptr;

    int getDiameter() const;

private:
    Q_DISABLE_COPY(QtMaterialBadge)
    Q_DECLARE_PRIVATE(QtMaterialBadge)

    // QWidget interface
public:
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALBADGE_H
