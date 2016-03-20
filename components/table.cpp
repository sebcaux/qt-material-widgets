#include <QDebug>
#include <QEvent>
#include <QHeaderView>
#include "table.h"
#include "style.h"

Table::Table(QWidget *parent)
    : QTableWidget(parent)
{
    setShowGrid(false);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    setStyle(&Style::instance());
}

Table::~Table()
{
}

void Table::paintEvent(QPaintEvent *event)
{
    QHeaderView *header = horizontalHeader();
    for (int i = 0; i < header->count(); ++i) {
        header->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    QTableWidget::paintEvent(event);
}
