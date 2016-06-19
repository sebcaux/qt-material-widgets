#ifndef PROGRESS_H
#define PROGRESS_H

#include <QProgressBar>
#include "lib/theme.h"

class ProgressPrivate;

class Progress : public QProgressBar
{
    Q_OBJECT

    Q_PROPERTY(QColor progressColor WRITE setProgressColor READ progressColor)
    Q_PROPERTY(QColor backgroundColor WRITE setProgressColor READ backgroundColor)

public:
    explicit Progress(QWidget *parent = 0);
    ~Progress();

    void setProgressType(Material::ProgressType type);
    Material::ProgressType progressType() const;

    void setUseThemeColors(bool state);
    bool useThemeColors() const;

    void setProgressColor(const QColor &color);
    QColor progressColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<ProgressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Progress)
    Q_DECLARE_PRIVATE(Progress)
};

#endif // PROGRESS_H
