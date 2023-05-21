#ifndef QTMATERIALAUTOCOMPLETE_H
#define QTMATERIALAUTOCOMPLETE_H

#include "qtmaterialwidgets.h"

#include "qtmaterialtextfield.h"

class QtMaterialAutoCompletePrivate;

class QTMATERIALWIDGETS_EXPORT QtMaterialAutoComplete : public QtMaterialTextField
{
    Q_OBJECT

public:
    explicit QtMaterialAutoComplete(QWidget *parent = nullptr);
    ~QtMaterialAutoComplete() override;

    void setDataSource(const QStringList &data);

signals:
    void itemSelected(QString);

protected slots:
    void updateResults(const QString &text);

private:
    Q_DISABLE_COPY(QtMaterialAutoComplete)
    Q_DECLARE_PRIVATE(QtMaterialAutoComplete)

    // QWidget interface
protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif  // QTMATERIALAUTOCOMPLETE_H
