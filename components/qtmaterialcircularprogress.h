#ifndef QTMATERIALCIRCULARPROGRESS_H
#define QTMATERIALCIRCULARPROGRESS_H

#include <QProgressBar>

#include "lib/qtmaterialtheme.h"

class QtMaterialCircularProgressPrivate;

class QtMaterialCircularProgress : public QProgressBar
{
    Q_OBJECT

    Q_PROPERTY(qreal lineWidth WRITE setLineWidth READ lineWidth)
    Q_PROPERTY(qreal size WRITE setSize READ size)
    Q_PROPERTY(QColor color WRITE setColor READ color)

public:
    explicit QtMaterialCircularProgress(QWidget *parent = nullptr);
    ~QtMaterialCircularProgress() override;

    void setProgressType(Material::ProgressType type);
    Material::ProgressType progressType() const;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setLineWidth(qreal width);
    qreal lineWidth() const;

    void setSize(int size);
    int size() const;

    void setColor(const QColor &color);
    QColor color() const;

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<QtMaterialCircularProgressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialCircularProgress)
    Q_DECLARE_PRIVATE(QtMaterialCircularProgress)
};

#endif  // QTMATERIALCIRCULARPROGRESS_H
