#ifndef PROGRESS_H
#define PROGRESS_H

#include <QWidget>

class ProgressPrivate;

class Progress : public QWidget
{
    Q_OBJECT

public:
    explicit Progress(QWidget *parent = 0);
    ~Progress();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<ProgressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Progress)
    Q_DECLARE_PRIVATE(Progress)
};

#endif // PROGRESS_H
