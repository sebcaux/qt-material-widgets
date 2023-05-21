#ifndef QTMATERIALSNACKBAR_H
#define QTMATERIALSNACKBAR_H

#include "qtmaterialwidgets.h"

#include "lib/qtmaterialoverlaywidget.h"

class QtMaterialSnackbarPrivate;

class QTMATERIALWIDGETS_EXPORT QtMaterialSnackbar : public QtMaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(bool clickToDismissMode READ clickToDismissMode WRITE setClickToDismissMode)
    Q_PROPERTY(int autoHideDuration READ autoHideDuration WRITE setAutoHideDuration)
    Q_PROPERTY(int boxWidth READ boxWidth WRITE setBoxWidth)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(qreal backgroundOpacity READ backgroundOpacity WRITE setBackgroundOpacity)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

public:
    explicit QtMaterialSnackbar(QWidget *parent = nullptr);
    ~QtMaterialSnackbar() override;

    bool clickToDismissMode() const;
    void setClickToDismissMode(bool value);

    int autoHideDuration() const;
    void setAutoHideDuration(int duration);

    int boxWidth() const;
    void setBoxWidth(int width);

    qreal fontSize() const;
    void setFontSize(qreal size);

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);
    qreal backgroundOpacity() const;
    void setBackgroundOpacity(qreal opacity);
    QColor textColor() const;
    void setTextColor(const QColor &color);

public slots:
    void addMessage(const QString &message);
    void addInstantMessage(const QString &message);

protected slots:
    void dequeue();

protected:
    const QScopedPointer<QtMaterialSnackbarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialSnackbar)
    Q_DECLARE_PRIVATE(QtMaterialSnackbar)

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALSNACKBAR_H
