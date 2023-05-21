#ifndef QTMATERIALSYSTEMBAR_H
#define QTMATERIALSYSTEMBAR_H

#include "qtmaterialwidgets.h"

#include <QWidget>

#include <QBasicTimer>

class QtMaterialSystemBarPrivate;

class QTMATERIALWIDGETS_EXPORT QtMaterialSystemBar : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialSystemBar(QWidget *parent = nullptr);
    ~QtMaterialSystemBar() override;

    const QString &dateTimeFormat() const;
    void setDateTimeFormat(const QString &dateTimeFormat);

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor textColor() const;
    void setTextColor(const QColor &color);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

protected:
    const QScopedPointer<QtMaterialSystemBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialSystemBar)
    Q_DECLARE_PRIVATE(QtMaterialSystemBar)

    // QObject interface
protected:
    bool event(QEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

    // QWidget interface
protected:
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALSYSTEMBAR_H
