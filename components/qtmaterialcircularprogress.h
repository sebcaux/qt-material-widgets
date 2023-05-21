#ifndef QTMATERIALCIRCULARPROGRESS_H
#define QTMATERIALCIRCULARPROGRESS_H

#include "qtmaterialwidgets.h"

#include <QProgressBar>

#include "lib/qtmaterialtheme.h"

class QtMaterialCircularProgressPrivate;

class QTMATERIALWIDGETS_EXPORT QtMaterialCircularProgress : public QProgressBar
{
    Q_OBJECT

    Q_PROPERTY(Material::ProgressType progressType READ progressType WRITE setProgressType)
    Q_PROPERTY(qreal lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(int size READ size WRITE setSize)
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit QtMaterialCircularProgress(QWidget *parent = nullptr);
    ~QtMaterialCircularProgress() override;

    Material::ProgressType progressType() const;
    void setProgressType(Material::ProgressType type);

    qreal lineWidth() const;
    void setLineWidth(qreal width);

    int size() const;
    void setSize(int size);

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor color() const;
    void setColor(const QColor &color);

protected:
    const QScopedPointer<QtMaterialCircularProgressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialCircularProgress)
    Q_DECLARE_PRIVATE(QtMaterialCircularProgress)

    // QWidget interface
public:
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALCIRCULARPROGRESS_H
