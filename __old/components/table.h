#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>

class Table : public QTableWidget
{
    Q_OBJECT

public:
    explicit Table(QWidget *parent = 0);
    ~Table();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};

#endif // TABLE_H
