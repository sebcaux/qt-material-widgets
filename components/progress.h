#ifndef PROGRESS_H
#define PROGRESS_H

#include <QProgressBar>
#include "lib/theme.h"

class ProgressPrivate;

class Progress : public QProgressBar
{
    Q_OBJECT

public:
    explicit Progress(QWidget *parent = 0);
    ~Progress();

    void setProgressType(Material::ProgressType type);
    Material::ProgressType progressType() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<ProgressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Progress)
    Q_DECLARE_PRIVATE(Progress)
};

#endif // PROGRESS_H
