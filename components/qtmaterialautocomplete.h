#ifndef QTMATERIALAUTOCOMPLETE_H
#define QTMATERIALAUTOCOMPLETE_H

#include "qtmaterialtextfield.h"

class QtMaterialAutoCompletePrivate;

class QtMaterialAutoComplete : public QtMaterialTextField
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

protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Q_DISABLE_COPY(QtMaterialAutoComplete)
    Q_DECLARE_PRIVATE(QtMaterialAutoComplete)
};

#endif  // QTMATERIALAUTOCOMPLETE_H
