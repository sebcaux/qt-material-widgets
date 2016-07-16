#ifndef QTMATERIALCHECKABLE_H
#define QTMATERIALCHECKABLE_H

#include <QAbstractButton>

class QtMaterialCheckablePrivate;

class QtMaterialCheckable : public QAbstractButton
{
    Q_OBJECT

public:
    explicit QtMaterialCheckable(QWidget *parent = 0);
    ~QtMaterialCheckable();

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    QtMaterialCheckable(QtMaterialCheckablePrivate &d, QWidget *parent = 0);

    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialCheckablePrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialCheckable)
    Q_DECLARE_PRIVATE(QtMaterialCheckable)
};

#endif // QTMATERIALCHECKABLE_H
