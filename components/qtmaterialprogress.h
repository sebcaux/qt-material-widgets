#ifndef QTMATERIALPROGRESS_H
#define QTMATERIALPROGRESS_H

#include "lib/qtmaterialtheme.h"
#include <QtWidgets/QProgressBar>

class QtMaterialProgressPrivate;

class QtMaterialProgress : public QProgressBar
{
    Q_OBJECT

    Q_PROPERTY(QColor progressColor WRITE setProgressColor READ progressColor)
    Q_PROPERTY(QColor backgroundColor WRITE setProgressColor READ backgroundColor)

public:
    explicit QtMaterialProgress(QWidget *parent = nullptr);
    ~QtMaterialProgress() override;

    void setProgressType(Material::ProgressType type);
    Material::ProgressType progressType() const;

    void setUseThemeColors(bool state);
    bool useThemeColors() const;

    void setProgressColor(const QColor &color);
    QColor progressColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

protected:
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<QtMaterialProgressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialProgress)
    Q_DECLARE_PRIVATE(QtMaterialProgress)
};

#endif  // QTMATERIALPROGRESS_H
