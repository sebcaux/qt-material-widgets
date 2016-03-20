#include "table.h"

Table::Table(QWidget *parent)
    : QTableWidget(parent)
{
    setShowGrid(false);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

Table::~Table()
{
}

bool Table::eventFilter(QObject *obj, QEvent *event)
{
    return QTableWidget::eventFilter(obj, event);
}
