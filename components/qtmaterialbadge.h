#ifndef QTMATERIALBADGE_H
#define QTMATERIALBADGE_H

#include "lib/qtmaterialoverlaywidget.h"

#include <QIcon>

class QtMaterialBadgePrivate;

class QtMaterialBadge : public QtMaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QPointF relativePosition READ relativePosition WRITE setRelativePosition)

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
