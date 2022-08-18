#ifndef QTMATERIALPROGRESS_H
#define QTMATERIALPROGRESS_H

#include <QProgressBar>

#include "lib/qtmaterialtheme.h"

class QtMaterialProgressPrivate;

class QtMaterialProgress : public QProgressBar
{
    Q_OBJECT

    Q_PROPERTY(Material::ProgressType progressType READ progressType WRITE setProgressType)
    Q_PROPERTY(QColor progressColor READ progressColor WRITE setProgressColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setProgressColor)

public:
    explicit QtMaterialProgress(QWidget *parent = nullptr);
    ~QtMaterialProgress() override;

    Material::ProgressType progressType() const;
    void setProgressType(Material::ProgressType type);

    bool useThemeColors() const;
    void setUseThemeColors(bool state);
    QColor progressColor() const;
    void setProgressColor(const QColor &color);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

protected:
    const QScopedPointer<QtMaterialProgressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialProgress)
    Q_DECLARE_PRIVATE(QtMaterialProgress)

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALPROGRESS_H
