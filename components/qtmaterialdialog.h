#ifndef QTMATERIALDIALOG_H
#define QTMATERIALDIALOG_H

#include "qtmaterialwidgets.h"

#include "lib/qtmaterialoverlaywidget.h"

#include <QScopedPointer>

class QLayout;
class QtMaterialDialogPrivate;

class QTMATERIALWIDGETS_EXPORT QtMaterialDialog : public QtMaterialOverlayWidget
{
    Q_OBJECT

public:
    explicit QtMaterialDialog(QWidget *parent = nullptr);
    ~QtMaterialDialog() override;

    QLayout *windowLayout() const;
    void setWindowLayout(QLayout *layout);

public slots:
    void showDialog();
    void hideDialog();

protected:
    const QScopedPointer<QtMaterialDialogPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialDialog)
    Q_DECLARE_PRIVATE(QtMaterialDialog)

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALDIALOG_H
